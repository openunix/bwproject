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
#define container_of(ptr, type, member)   ((type *)((char *)ptr - (char *)(&((type *)0)->member)))

/* when use static inline*/ 
#ifdef _MSC_VER
#define INLINE __inline
#else
#define INLINE inline
#endif

# include "F:/bwlib/bwoss/win_user/win_user_oss.h"

/* 
 * Windows user space external fuctions
 */

static INLINE void *bwoss_malloc(unsigned int size)
{
	return malloc(size);
}

static INLINE void bwoss_free(void* ptr)
{
	free(ptr);
} 

static INLINE  void bwoss_initialize_lock()
{
    initialize_lock();
}
static INLINE  void bwoss_clean_lock()
{
	clean_lock();
}

/* locker functions*/        
static INLINE  int bwoss_unlock_write()
{
       return unlock_write();
}

static INLINE int bwoss_lock_write()
{
      return lock_write();;
}
static INLINE  bwoss_unlock_read() 
{
	return unlock_read();
}
static INLINE  bwoss_lock_read()
{
    return lock_read();
}  


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
