/* EMX File System Module's Super Block Operations */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/writeback.h>
#include <linux/errno.h>

#include "emxfs.h"

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,34))
static int emxfs_super_write_inode(struct inode *inode, int do_sync)
{
#else
static int emxfs_super_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int do_sync = (wbc->sync_mode == WB_SYNC_ALL);
#endif
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh;
	struct emxfs_inode *emxfs_inode;
	struct emxfs_sb *emxfs_sb = ((struct emxfs_fs_info *)(sb->s_fs_info))->emxfs_sb;
	int i;

	printk(KERN_INFO "emx_fs: emxfs_super_write_inode (i_ino = %ld) = %lld bytes\n",
		inode->i_ino, i_size_read(inode));

	if (!(emxfs_inode = emxfs_get_inode(sb, inode->i_ino, &bh)))
	{
		printk (KERN_ERR "emx_fs: unable to read inode\n");
		return -EIO;
	}
	if ((inode->i_mode & S_IFREG) && (emxfs_inode->file_size >= 0))
   	{
		emxfs_inode->file_size = i_size_read(inode);
		for (i = (emxfs_inode->file_size + emxfs_sb->block_size - 1) /
					emxfs_sb->block_size; i < EMXFS_MAX_BLOCKS_PER_FILE; i++)
		{
			if (emxfs_inode->u.file_blocks[i])
			{
				emxfs_put_free_block(sb, emxfs_inode->u.file_blocks[i]);
				// Even if the put fails, let's mark it free
				emxfs_inode->u.file_blocks[i] = 0;
			}
		}
		mark_buffer_dirty(bh);
		if (do_sync)
		{
			sync_dirty_buffer(bh);
			if (buffer_req(bh) && !buffer_uptodate(bh))
			{
				printk ("emxfs: IO error syncing inode [%s:%08lx]\n",
						sb->s_id, inode->i_ino);
				brelse(bh);
				return -EIO;
			}
		}

	}
	brelse(bh);

	return 0;
}

struct super_operations emxfs_sops =
{
	statfs: simple_statfs, /* handler from libfs */
	write_inode: emxfs_super_write_inode
};

MODULE_LICENSE("GPL");
