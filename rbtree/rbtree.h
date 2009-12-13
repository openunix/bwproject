/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * rbtree.c - implement of the functions 
 * exported by bwlib.
 * 
 * Dependencies: None (Should be self-defined)
 *
 * ChangeLog:
 *  2009-12-2 Initial Created
 * ToDo:
 *  None
 */

 /* 
  * Copyright (c) 2009 Institute of Computing Technology,
  *                    Chinese Academy of Sciences
  * 
  * Author:  
  */

#ifndef RB_NODE
#define RB_NODE

#include <stdio.h>
#include "../bwlib.h"

#define RB_RED 0
#define RB_BLACK 1

#define EMPTY_ROOT -2
#define KEY_EXIST -3

#define rb_color(x) ((x)->parent & 3)
#define rb_parent(x) ((bwlib_rb_node_t *)((x)->parent & (~3)))
#define rb_set_red(x) ((x)->parent &= ~1)
#define rb_set_black(x) ((x)->parent |= 1) 
#define rb_is_red(x) (!rb_color(x))
#define rb_is_black(x) (rb_color(x))

#define is_null_node(x) ((x) == &null_node)

#endif



