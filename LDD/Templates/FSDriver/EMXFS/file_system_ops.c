/* EMX File System Module's File System Operations */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/slab.h>
#include <linux/errno.h>

#include "emxfs.h"

static int get_bit_pos(unsigned int val)
{
	int i;

	for (i = 0; val; i++)
	{
		val >>= 1;
	}
	return (i - 1);
}

static int emxfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct buffer_head *bh, *bh2;
	struct emxfs_fs_info *emxfs_fs_info;
	struct emxfs_sb *emxfs_sb;
	struct inode *root_inode;
	struct emxfs_inode *emxfs_root_inode;

	printk(KERN_INFO "emx_fs: emxfs_fill_super\n");

	if (!(emxfs_fs_info = (struct emxfs_fs_info *)
							(kzalloc(sizeof(struct emxfs_fs_info), GFP_KERNEL))))
	/* If all goes fine, this emxfs_fs_info will be kfree in emxfs_kill_sb */
	{
		printk (KERN_ERR "emx_fs: unable to allocate memory for fs info\n");
		return -ENOMEM;
	}
	if (!(bh = sb_bread(sb, 0 /* First block */)))
	/* If all goes fine, this bh will be brelse in emxfs_kill_sb */
	{
		printk (KERN_ERR "emx_fs: unable to read super block\n");
		kfree(emxfs_fs_info);
		return -EIO;
	}
	emxfs_fs_info->bh = bh;
	emxfs_sb = (struct emxfs_sb *)(bh->b_data);
	emxfs_fs_info->emxfs_sb = emxfs_sb;
	if (emxfs_sb->fs_type != EMXFS_SUPER_MAGIC)
	{
		printk (KERN_ERR "emx_fs: unable to find emx fs\n");
		brelse(bh);
		kfree(emxfs_fs_info);
		return -EINVAL;
	}
	sb->s_fs_info = emxfs_fs_info;
	sb->s_blocksize = emxfs_sb->block_size;
	sb->s_blocksize_bits = get_bit_pos(sb->s_blocksize);
	sb->s_magic = emxfs_sb->fs_type;
	sb->s_op = &emxfs_sops; // super block operations
	sb->s_type = &emxfs; // file system type
	printk(KERN_INFO "emx_fs: BS: %ld bytes = (1 << %d); Magic: 0x%lX; Root Inode: %d\n",
		sb->s_blocksize, sb->s_blocksize_bits, sb->s_magic, emxfs_sb->root_inode);

	root_inode = iget_locked(sb, emxfs_sb->root_inode); // allocate an inode
	if (!root_inode)
	{
		sb->s_fs_info = NULL;
		brelse(bh);
		kfree(emxfs_fs_info);
		return -EACCES;
	}
	if (root_inode->i_state & I_NEW)
	{
		if (!(emxfs_root_inode = emxfs_get_inode(sb, emxfs_sb->root_inode, &bh2)))
		{
			printk (KERN_ERR "emx_fs: unable to read root inode\n");
			iget_failed(root_inode);
			sb->s_fs_info = NULL;
			brelse(bh);
			kfree(emxfs_fs_info);
			return -EIO;
		}
		if (strncmp(emxfs_root_inode->file_name, "/", EMXFS_MAX_FILE_NAME_SIZE))
		{
			brelse(bh2);
			iget_failed(root_inode);
			sb->s_fs_info = NULL;
			brelse(bh);
			kfree(emxfs_fs_info);
			return -EINVAL;
		}
		printk(KERN_INFO "emx_fs: Got new root inode, let's fill in\n");
		root_inode->i_mode = emxfs_get_inode_flags(emxfs_root_inode);
		root_inode->i_op = &emxfs_iops; // set the inode ops
		root_inode->i_mapping->a_ops = &emxfs_aops;
		root_inode->i_fop = &emxfs_fops;
		brelse(bh2);
		unlock_new_inode(root_inode);
	}
	else
	{
		printk(KERN_INFO "emx_fs: Got root inode from inode cache\n");
	}
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0))
	sb->s_root = d_alloc_root(root_inode);
#else
	sb->s_root = d_make_root(root_inode);
#endif
	if (!sb->s_root)
	{
		iget_failed(root_inode);
		sb->s_fs_info = NULL;
		brelse(bh);
		kfree(emxfs_fs_info);
		return -ENOMEM;
	}

	return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38))
static int emxfs_get_sb(struct file_system_type *fs_type, int flags, const char *devname, void *data, struct vfsmount *vm)
{
	printk(KERN_INFO "emx_fs: emxfs_get_sb\n");
	printk(KERN_INFO "emx_fs: devname = %s\n", devname);

	 /* emxfs_fill_super this will be called to fill the super block */
	return get_sb_bdev(fs_type, flags, devname, data, &emxfs_fill_super, vm);
}
#else
static struct dentry *emxfs_mount(struct file_system_type *fs_type, int flags, const char *devname, void *data)
{
	printk(KERN_INFO "emx_fs: emxfs_mount\n");
	printk(KERN_INFO "emx_fs: devname = %s\n", devname);

	 /* emxfs_fill_super this will be called to fill the super block */
	return mount_bdev(fs_type, flags, devname, data, &emxfs_fill_super);
}
#endif

static void emxfs_kill_sb(struct super_block *sb)
{
	struct emxfs_fs_info *emxfs_fs_info = (struct emxfs_fs_info *)(sb->s_fs_info);

	printk(KERN_INFO "emx_fs: emxfs_kill_sb\n");

	if (emxfs_fs_info)
	{
		if (emxfs_fs_info->bh)
		{
			brelse(emxfs_fs_info->bh);
		}
		kfree(emxfs_fs_info);
	}
	kill_block_super(sb);
}

struct file_system_type emxfs =
{
	name: "emx",
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38))
	get_sb:  emxfs_get_sb,
#else
	mount:  emxfs_mount,
#endif
	kill_sb: emxfs_kill_sb,
	owner: THIS_MODULE
};

MODULE_LICENSE("GPL");
