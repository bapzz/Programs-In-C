# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)

	KERNEL_SOURCE := /usr/src/linux-headers-`uname -r`
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else

	obj-m := emx_simple.o emx.o sfs_bb.o sfs_first.o sfs_final.o
	emx-src-m := $(notdir $(wildcard ${SUBDIRS}/emxFS/*.c))
	emx-y := $(addprefix EMXFS/,$(emx-src-m:.c=.o))
	sfs_bb-y := $(addprefix SFS/,real_sfs_bb.o)
	sfs_first-y := $(addprefix SFS/,real_sfs_minimal.o real_sfs_ops.o)
	sfs_final-y := $(addprefix SFS/,real_sfs.o real_sfs_ops.o)

endif
