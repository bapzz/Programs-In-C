/* EMX File System Module's Address Operations */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/mpage.h>
#include <linux/errno.h>

#include "emxfs.h"

static int emxfs_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh;
	struct emxfs_inode *emxfs_inode;
	sector_t phys;

	printk(KERN_INFO "emx_fs: emxfs_get_block called for I: %ld, B: %lld, C: %d\n",
			inode->i_ino, iblock, create);

	if (iblock >= EMXFS_MAX_BLOCKS_PER_FILE)
	{
		return -ENOSPC;
	}

	if (!(emxfs_inode = emxfs_get_inode(sb, inode->i_ino, &bh)))
	{
		printk (KERN_ERR "emx_fs: unable to read inode to get blocks\n");
		return -EIO;
	}
	if (!emxfs_inode->u.file_blocks[iblock])
	{
		if (!create)
		{
			brelse(bh);
			return -EIO;
		}
		else
		{
			if (!(emxfs_inode->u.file_blocks[iblock] = emxfs_get_free_block(sb)))
			{
				brelse(bh);
				return -ENOSPC;
			}
			mark_buffer_dirty(bh);
		}
	}
	phys = emxfs_inode->u.file_blocks[iblock];
	brelse(bh);

	map_bh(bh_result, sb, phys);

	return 0;
}

static int emxfs_readpage(struct file *file, struct page *page)
{
	return mpage_readpage(page, emxfs_get_block);
}

static int emxfs_writepage(struct page *page, struct writeback_control *wbc)
{
	return block_write_full_page(page, emxfs_get_block, wbc);
}

static int emxfs_write_begin(struct file *file, struct address_space *mapping,
	loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
{
	*pagep = NULL;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
	return block_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
		emxfs_get_block);
#else
	return block_write_begin(mapping, pos, len, flags, pagep, emxfs_get_block);
#endif
}

struct address_space_operations emxfs_aops =
{
	.readpage = emxfs_readpage,
	.writepage = emxfs_writepage,
	.write_begin = emxfs_write_begin,
	.write_end = generic_write_end,
};

MODULE_LICENSE("GPL");
