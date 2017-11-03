/* EMX File System Module's Inode Operations */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/errno.h>

#include "emxfs.h"

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0))
static struct dentry *emxfs_inode_lookup(struct inode *parent_inode, struct dentry *dentry, struct nameidata *nameidata)
#else
static struct dentry *emxfs_inode_lookup(struct inode *parent_inode, struct dentry *dentry, unsigned int flags)
#endif
{
	struct super_block *sb = parent_inode->i_sb;
	struct buffer_head *bh, *bh2;
	struct emxfs_inode *emxfs_inode, *emxfs_inode2;
	int i;
	struct inode *file_inode;

	printk(KERN_INFO "emx_fs: emxfs_inode_lookup\n");

	if (!(emxfs_inode = emxfs_get_inode(sb, parent_inode->i_ino, &bh)))
	{
		printk (KERN_ERR "emx_fs: unable to read parent inode\n");
		return ERR_PTR(-EIO);
	}
	for (i = 0; i < EMXFS_MAX_ENTRIES_PER_DIR; i++)
	{
		if (emxfs_inode->u.dir_entries[i])
		{
			if (!(emxfs_inode2 =
						emxfs_get_inode(sb, emxfs_inode->u.dir_entries[i], &bh2)))
			{
				printk (KERN_ERR "emx_fs: unable to read inode\n");
				brelse(bh);
				return ERR_PTR(-EIO);
			}
			if (strncmp(dentry->d_name.name, emxfs_inode2->file_name,
						EMXFS_MAX_FILE_NAME_SIZE))
			{
				brelse(bh2);
			}
			else
			{
				break;
			}
		}
	}
	if (i == EMXFS_MAX_ENTRIES_PER_DIR)
	{
		brelse(bh);
		return ERR_PTR(-ENOENT);
	}

	printk(KERN_INFO "emx_fs: Getting an inode\n");
	file_inode = iget_locked(sb, emxfs_inode->u.dir_entries[i]);
	if (!file_inode)
	{
		brelse(bh2);
		brelse(bh);
		return ERR_PTR(-EACCES);
	}
	if (file_inode->i_state & I_NEW)
	{
		printk(KERN_INFO "emx_fs: Got new inode, let's fill in\n");
		file_inode->i_size = emxfs_inode2->file_size;
		file_inode->i_mode = emxfs_get_inode_flags(emxfs_inode2);
		file_inode->i_mapping->a_ops = &emxfs_aops;
		file_inode->i_fop = &emxfs_fops;
		unlock_new_inode(file_inode);
	}
	else
	{
		printk(KERN_INFO "emx_fs: Got inode from inode cache\n");
	}
	d_add(dentry, file_inode);
	brelse(bh2);
	brelse(bh);

	return NULL;
}

struct inode_operations emxfs_iops =
{
	lookup: emxfs_inode_lookup
};

MODULE_LICENSE("GPL");
