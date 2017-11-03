#ifndef EMXFS_H
#define EMXFS_H

#define EMXFS_SUPER_MAGIC 0xABCD
#define EMXFS_MAX_FILE_NAME_SIZE 16
#define EMXFS_MAX_BLOCKS_PER_FILE (3 + 24)
#define EMXFS_MAX_ENTRIES_PER_DIR EMXFS_MAX_BLOCKS_PER_FILE
#define EMXFS_MAX_ACTUAL_FILE_PATH_SIZE (EMXFS_MAX_BLOCKS_PER_FILE * sizeof(int))

enum file_type
{
	emxfs_dir = -1,
	emxfs_link = -2
};

struct emxfs_sb
{
	unsigned short fs_type;
	unsigned short block_size;
	unsigned int block_cnt;
	unsigned int inodes_per_block;
	unsigned int inodes_block_start;
	unsigned int inodes_block_cnt;
	unsigned int free_bits_per_block;
	unsigned int free_bits_block_start;
	unsigned int free_bits_block_cnt;
	unsigned int data_block_start;
	unsigned int data_block_cnt;
	unsigned int root_inode;
};
struct emxfs_inode
{
	char file_name[EMXFS_MAX_FILE_NAME_SIZE];
	int file_size; // -1: directory; -2: link
	union
	{
		unsigned int file_blocks[EMXFS_MAX_BLOCKS_PER_FILE];
		unsigned int dir_entries[EMXFS_MAX_ENTRIES_PER_DIR];
		char actual_file_path[EMXFS_MAX_ACTUAL_FILE_PATH_SIZE];
	} u;
};

#ifdef __KERNEL__
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/types.h>

struct emxfs_fs_info
{
	struct emxfs_sb *emxfs_sb;
	struct buffer_head *bh;
};

extern struct file_system_type emxfs;
extern struct super_operations emxfs_sops;
extern struct inode_operations emxfs_iops;
extern struct address_space_operations emxfs_aops;
extern struct file_operations emxfs_fops;

/*
 * Caller of the following function is expected to do brelse(*bhp), after done using
 * the return pointer
 */
extern struct emxfs_inode *emxfs_get_inode(struct super_block *sb, int ino,
	struct buffer_head **bhp);
extern umode_t emxfs_get_file_type(struct emxfs_inode *i);
extern umode_t emxfs_get_inode_flags(struct emxfs_inode *i);
extern unsigned int emxfs_get_free_block(struct super_block *sb);
int emxfs_put_free_block(struct super_block *sb, int block_no);
#endif
#endif
