/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * win_user_oss.h - This file contains all the function prototypes
 * that are exported by  windows OS service.
 * 
 * 
 * Dependencies:
 * stdio.h£¬windows.h,malloc.h
 *
 * ChangeLog: 2009-12-2 Initial Created
 * 
 * ToDo:
 *  None
 */

 /* 
  * Copyright (c) 2009 Institute of Computing Technology,
  *                    Chinese Academy of Sciences
  * 
  * Author:  
  */
#ifndef WIN_USER_OSS_H
#define WIN_USER_OSS_H

#include "stdio.h"
#include "windows.h"
#include "malloc.h"


void initialize_lock();
void clean_lock();

/* locker functions*/        
int unlock_write();
int lock_write();
int unlock_read();
int lock_read();

/* a little more functions*/ 
int get_waiting_writers();
int get_waiting_readers();
int get_lock_count();


#endif