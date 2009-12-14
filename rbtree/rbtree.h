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

#define RB_RED 0
#define RB_BLACK 1

#include <stdio.h>
#include "bwlib.h"

#define rb_parent(x) ((bwlib_rb_node_t *)((x)->parent & (~3)))
#define rb_color(x) ((x)->parent & 1)
#define rb_is_red(x) (!rb_color(x))
#define rb_is_black(x) (rb_color(x))
#define rb_set_red(x) ((x)->parent &= ~1)
#define rb_set_black(x) ((x)->parent |= 1) 

static inline void rb_set_parent(bwlib_rb_node_t *rb, bwlib_rb_node_t *p)
{
	rb->parent = (rb->parent & 3) | (unsigned long)p;
}
static inline void rb_set_color(bwlib_rb_node_t *rb, int color)
{
	rb->parent = (rb->parent & ~1) | color;
}

#define RB_EMPTY_ROOT(root)	((root)->rb_node == NULL)
#define RB_EMPTY_NODE(node)	(parent(node) == node)
#define RB_CLEAR_NODE(node)	(rb_set_parent(node, node))

#endif
