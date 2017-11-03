#ifndef PARTITION_H
#define PARTITION_H

#include <linux/types.h>
#include <linux/module.h> 

extern void copy_mbr_n_br(u8 *disk);
#endif
