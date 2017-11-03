/* Simple File System Module */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mpage.h>
#include <linux/pagemap.h>
#include <linux/writeback.h>
#include <linux/buffer_head.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#define USE_DDKB 1

#define EMXFS_SUPER_MAGIC 0xABCD
#define FILE_INODE_NUMBER 2
#define DATA_BLOCK_OFFSET 0 // Some number in [0, BLOCKS_IN_BLOCK_DEVICE - 1]
#ifndef USE_DDKB
#define EMXFS_BLOCK_SIZE PAGE_SIZE
#define EMXFS_BLOCK_SIZE_BITS PAGE_CACHE_SHIFT
#else
#define EMXFS_BLOCK_SIZE 512
#define EMXFS_BLOCK_SIZE_BITS 9
#endif
#ifndef USE_DDKB
/* If using rb.ko, we'll use /dev/rb1, which is configured for 288 sectors */
#define BLOCK_DEVICE_SIZE (288 * 512) /* Sectors * Sector Size */
#else
/* If using ddkb.ko, we'll use /dev/ddk, which is configured for 1 sector */
#define BLOCK_DEVICE_SIZE (1 * 512) /* Sectors * Sector Size */
#endif
/* Based on the above, assuming the size of the block device getting mounted underneath */
#define BLOCKS_IN_BLOCK_DEVICE (BLOCK_DEVICE_SIZE / EMXFS_BLOCK_SIZE)

/*
 * Data declarations
 */

static struct inode *emxsfs_root_inode;

static char filename[] = "moksha.txt";
static char filename2[] = "world.txt";
static int filename_len = sizeof(filename) - 1;
static int filename2_len = sizeof(filename2) - 1;

static int file_size = 12;

/*
 * File Operations
 */

static int emxsfs_file_open(struct inode *inode, struct file *file)
{
	return generic_file_open(inode, file);
}

static int emxsfs_file_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t emxsfs_file_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "emx_simple_fs: emxsfs_file_read max_readahead = %d\n", file->f_ra.ra_pages);

	file->f_ra.ra_pages = 0; /* No read-ahead */
	return do_sync_read(file, buf, len, off);
}

static ssize_t emxsfs_file_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "emx_simple_fs: emxsfs_file_write\n");

	return do_sync_write(file, buf, len, off);
}

static int emxsfs_file_readdir(struct file *file, void *dirent, filldir_t filldir)
static int emxsfs_file_readdir(struct file *file, struct dir_context *ctx)
{
	struct dentry *de = file->f_dentry;

	printk(KERN_INFO "emx_simple_fs: emxsfs_file_readdir\n");

	if (file->f_pos > 0)
	{
		return 0;
	}
	if (filldir(dirent, ".", 1, file->f_pos++, de->d_inode->i_ino, DT_DIR) ||
	    filldir(dirent, "..", 2, file->f_pos++, de->d_parent->d_inode->i_ino, DT_DIR))
	{
		return -ENOSPC;
	}
	if (filldir(dirent, filename, filename_len, file->f_pos++, FILE_INODE_NUMBER, DT_REG))
	{
		return -ENOSPC;
	}
	if (filldir(dirent, filename2, filename2_len, file->f_pos++, FILE_INODE_NUMBER, DT_REG))
	{
		return -ENOSPC;
	}
	return 0;
}

static struct file_operations emxsfs_fops =
{
	open: emxsfs_file_open,
	release: emxsfs_file_release,
	read: emxsfs_file_read,
	write: emxsfs_file_write,
	aio_read: generic_file_aio_read,
	aio_write: generic_file_aio_write,
	readdir: emxsfs_file_readdir,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
	fsync: simple_sync_file
#else
	fsync: noop_fsync
#endif
};

static int emxsfs_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	sector_t phys;

	printk(KERN_INFO "emx_simple_fs: emxsfs_get_block called for I: %ld, B: %lld, C: %d\n",
			inode->i_ino, iblock, create);

	if (inode->i_ino != FILE_INODE_NUMBER)
	{
		return -EIO;
	}
	if (iblock >= (BLOCKS_IN_BLOCK_DEVICE - DATA_BLOCK_OFFSET))
	{
		return -ENOSPC;
	}
	phys = DATA_BLOCK_OFFSET + iblock;
	map_bh(bh_result, sb, phys);

	return 0;
}

static int emxsfs_readpage(struct file *file, struct page *page)
{
	return mpage_readpage(page, emxsfs_get_block);
}

static int emxsfs_writepage(struct page *page, struct writeback_control *wbc)
{
	return block_write_full_page(page, emxsfs_get_block, wbc);
}

static int emxsfs_write_begin(struct file *file, struct address_space *mapping,
	loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
{
	*pagep = NULL;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
	return block_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
		emxsfs_get_block);
#else
	return block_write_begin(mapping, pos, len, flags, pagep, emxsfs_get_block);
#endif
}

static struct address_space_operations emxsfs_aops =
{
	.readpage = emxsfs_readpage,
	.writepage = emxsfs_writepage,
	.write_begin = emxsfs_write_begin,
	.write_end = generic_write_end,
};

/*
 * Inode Operations
 */

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0))
static struct dentry *emxsfs_inode_lookup(struct inode *parent_inode, struct dentry *dentry, struct nameidata *nameidata)
#else
static struct dentry *emxsfs_inode_lookup(struct inode *parent_inode, struct dentry *dentry, unsigned int flags)
#endif
{
	struct inode *file_inode;

	printk(KERN_INFO "emx_simple_fs: emxsfs_inode_lookup\n");

	if (parent_inode->i_ino != emxsfs_root_inode->i_ino)
		return ERR_PTR(-ENOENT);
	if ((dentry->d_name.len != filename_len ||
		 strncmp(dentry->d_name.name, filename, dentry->d_name.len)) &&
		(dentry->d_name.len != filename2_len ||
		 strncmp(dentry->d_name.name, filename2, dentry->d_name.len)))
	  return ERR_PTR(-ENOENT);

	printk(KERN_INFO "emx_simple_fs: Getting an inode\n");
	file_inode = iget_locked(parent_inode->i_sb, FILE_INODE_NUMBER);
	if (!file_inode)
		return ERR_PTR(-EACCES);
	if (file_inode->i_state & I_NEW)
	{
		printk(KERN_INFO "emx_simple_fs: Got new inode, let's fill in\n");
		file_inode->i_size = file_size;
		file_inode->i_mode = S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		file_inode->i_mapping->a_ops = &emxsfs_aops;
		file_inode->i_fop = &emxsfs_fops;
		unlock_new_inode(file_inode);
	}
	else
	{
		printk(KERN_INFO "emx_simple_fs: Got inode from inode cache\n");
	}
	d_add(dentry, file_inode);

	return NULL;
}

static struct inode_operations emxsfs_iops =
{
	lookup: emxsfs_inode_lookup
};

/*
 * Super-Block Operations
 */

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,34))
static int emxsfs_super_write_inode(struct inode *inode, int do_sync)
#else
static int emxsfs_super_write_inode(struct inode *inode, struct writeback_control *wbc)
#endif
{
	printk(KERN_INFO "emx_simple_fs: emxsfs_super_write_inode (i_ino = %ld) = %lld\n",
		inode->i_ino, i_size_read(inode));

	if (inode->i_ino == FILE_INODE_NUMBER)
   	{
		file_size = i_size_read(inode);
	}
	return 0;
}

static struct super_operations emxsfs_sops =
{
	statfs: simple_statfs, /* handler from libfs. Try df -a[T] */
	write_inode: emxsfs_super_write_inode
};

/*
 * File-System Operations
 */

static int emxsfs_fill_super(struct super_block *sb, void *data, int silent);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38))
static int emxsfs_get_sb(struct file_system_type *fs_type, int flags, const char *devname, void *data, struct vfsmount *vm)
{
	printk(KERN_INFO "emx_simple_fs: devname = %s\n", devname);

	 /* emxsfs_fill_super this will be called to fill the super block */
	return get_sb_bdev(fs_type, flags, devname, data, &emxsfs_fill_super, vm);
}
#else
static struct dentry *emxsfs_mount(struct file_system_type *fs_type, int flags, const char *devname, void *data)
{
	printk(KERN_INFO "emx_simple_fs: devname = %s\n", devname);

	 /* emxsfs_fill_super this will be called to fill the super block */
	return mount_bdev(fs_type, flags, devname, data, &emxsfs_fill_super);
}
#endif

static void emxsfs_kill_sb(struct super_block *sb)
{
	kill_block_super(sb);
}

static struct file_system_type emxsfs =
{
	name: "emx_simple",
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38))
	get_sb:  emxsfs_get_sb,
#else
	mount:  emxsfs_mount,
#endif
	kill_sb: emxsfs_kill_sb,
	owner: THIS_MODULE
};

static int emxsfs_fill_super(struct super_block *sb, void *data, int silent)
{
	printk(KERN_INFO "emx_simple_fs: emxsfs_fill_super\n");

	sb->s_blocksize = EMXFS_BLOCK_SIZE;
	sb->s_blocksize_bits = EMXFS_BLOCK_SIZE_BITS;
	sb->s_magic = EMXFS_SUPER_MAGIC;
	sb->s_op = &emxsfs_sops; // super block operations
	sb->s_type = &emxsfs; // file_system_type

	emxsfs_root_inode = iget_locked(sb, 1); // allocate an inode
	if (!emxsfs_root_inode)
	{
		return -EACCES;
	}
	if (emxsfs_root_inode->i_state & I_NEW)
	{
		printk(KERN_INFO "emx_simple_fs: Got new root inode, let's fill in\n");
		emxsfs_root_inode->i_op = &emxsfs_iops; // set the inode ops
		emxsfs_root_inode->i_mode = S_IFDIR | S_IRWXU |
			S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
		emxsfs_root_inode->i_mapping->a_ops = &emxsfs_aops;
		emxsfs_root_inode->i_fop = &emxsfs_fops;
		unlock_new_inode(emxsfs_root_inode);
	}
	else
	{
		printk(KERN_INFO "emx_simple_fs: Got root inode from inode cache\n");
	}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0))
	sb->s_root = d_alloc_root(emxsfs_root_inode);
#else
	sb->s_root = d_make_root(emxsfs_root_inode);
#endif
	if (!sb->s_root)
	{
		iget_failed(emxsfs_root_inode);
		return -ENOMEM;
	}

	return 0;
}

static int __init emx_simple_init(void)
{
	int err;

	err = register_filesystem(&emxsfs);
	return err;
}

static void __exit emx_simple_exit(void)
{
	unregister_filesystem(&emxsfs);
}

module_init(emx_simple_init);
module_exit(emx_simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("File System Module for EMX Simple File System");
