/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * bwoss_iface.h - This file contains all the external function
 * prototypes that are exported by BWOSS (BWFS Operating System
 * Service).
 * 
 * Dependencies:
 *  bwoss/win_user/win_user_oss.h - OSS for Windows User Space
 *  bwoss/win_kern/win_kern_oss.h - OSS for Windows Kernel Space
 *  bwoss/lin_user/lin_user_oss.h - OSS for Linux User Space
 *  bwoss/lin_kern/lin_kern_oss.h - OSS for Linux Kernel Space
 *
 * ChangeLog:
 *  2009-12-2 Initial Created
 * ToDo:
 *  None
 */

 /* 
 * Copyright (c) 2009 Institute of Computing Technology
 * Author:  
 */

#ifndef _BWOSS_IFACE_H
#define _BWOSS_IFACE_H

#if defined BWOSS_WINDOWS_USER
/* 
 * Windows user space defines and macros
 */
# include "bwoss/win_user/win_user_oss.h"

/* 
 * Windows user space external fuctions
 */


#elif defined BWOSS_WINDOWS_KERNEL
/* 
 * Windows kernel space defines and macros
 */
# include "bwoss/win_kern/win_kern_oss.h"

/* 
 * Windows kernel space external fuctions
 */


#elif defined BWOSS_LINUX_USER
/* 
 * Linux user space defines and macros
 */
# include "bwoss/lin_user/lin_user_oss.h"

/* 
 * Linux user space external fuctions
 */


#elif defined BWOSS_LINUX_KERNEL
/* 
 * Linux kernel space defines and macros
 */
# include "bwoss/lin_kern/lin_kern_oss.h"

/* 
 * Linux kernel space external fuctions
 */


#else
# error "You need to define at least one compile flag!"
#endif

/* 
 * Common external fuctions and macros
 */

#endif /* _BWOSS_IFACE_H */
