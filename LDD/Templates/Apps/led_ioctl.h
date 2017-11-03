#ifndef LED_IOCTL_H

#define LED_IOCTL_H

#include <linux/ioctl.h>

#define LED_SET_CHAR_DELAY _IOW('l', 1, int)
#define LED_GET_CHAR_DELAY _IOR('l', 2, int *)

#endif
