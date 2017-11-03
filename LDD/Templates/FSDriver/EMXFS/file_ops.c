/* EMX File System Module's File Operations */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/errno.h>

#include "emxfs.h"

static int emxfs_file_open(struct inode *inode, struct file *file)
{
	return generic_file_open(inode, file);
}

static int emxfs_file_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t emxfs_file_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "emx_fs: emxfs_file_read max_readahead = %d\n", file->f_ra.ra_pages);

	file->f_ra.ra_pages = 0; /* No read-ahead */
	return do_sync_read(file, buf, len, off);
}

static ssize_t emxfs_file_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "emx_fs: emxfs_file_write\n");

	return do_sync_write(file, buf, len, off);
}

static int emxfs_file_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct dentry *de = file->f_dentry;
	struct super_block *sb = de->d_inode->i_sb;
	struct buffer_head *bh, *bh2;
	struct emxfs_inode *emxfs_inode, *emxfs_inode2;
	int i, pos, retval;

	printk(KERN_INFO "emx_fs: emxfs_file_readdir\n");

	if (file->f_pos >= (2 + EMXFS_MAX_ENTRIES_PER_DIR))
	{
		return 0;
	}
	if (file->f_pos == 0)
	{
		retval = filldir(dirent, ".", 1, file->f_pos, de->d_inode->i_ino, DT_DIR);
		if (retval)
		{
			return retval;
		}
		file->f_pos++;
	}
	if (file->f_pos == 1)
	{
		retval = filldir(dirent, "..", 2, file->f_pos, de->d_parent->d_inode->i_ino, DT_DIR);
		if (retval)
		{
			return retval;
		}
		file->f_pos++;
	}
	pos = 1; /* For . & .. */
	if (!(emxfs_inode = emxfs_get_inode(sb, de->d_inode->i_ino, &bh)))
	{
		printk (KERN_ERR "emx_fs: unable to read parent inode\n");
		return -EIO;
	}
	for (i = 0; i < EMXFS_MAX_ENTRIES_PER_DIR; i++)
	{
		if (emxfs_inode->u.dir_entries[i])
		{
			pos++;
			if (!(emxfs_inode2 =
						emxfs_get_inode(sb, emxfs_inode->u.dir_entries[i], &bh2)))
			{
				printk (KERN_ERR "emx_fs: unable to read inode\n");
				brelse(bh);
				return -EIO;
			}
			if (pos == file->f_pos)
			{
				retval = filldir(dirent, emxfs_inode2->file_name,
						strnlen(emxfs_inode2->file_name, EMXFS_MAX_FILE_NAME_SIZE),
						file->f_pos, emxfs_inode->u.dir_entries[i],
						emxfs_get_file_type(emxfs_inode2));
				if (retval)
				{
					brelse(bh2);
					brelse(bh);
					return retval;
				}
				file->f_pos++;
			}
			brelse(bh2);
		}
	}
	brelse(bh);
	return 0;
}

struct file_operations emxfs_fops =
{
	open: emxfs_file_open,
	release: emxfs_file_release,
	read: emxfs_file_read,
	write: emxfs_file_write,
	aio_read: generic_file_aio_read,
	aio_write: generic_file_aio_write,
	readdir: emxfs_file_readdir,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
	fsync: simple_sync_file
#else
	fsync: noop_fsync
#endif
};

MODULE_LICENSE("GPL");
