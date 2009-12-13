/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * bwlib.h - This file contains all the function prototypes that are
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

#include <stdio.h>
#include "../bwlib.h"
#include "rbtree.h"

extern null_node;
typedef struct mynode_s
{
	unsigned long key;
	bwlib_rb_node_t node;	
}mynode;

#define rb_key(p) ((bwlib_rb_entry((p), mynode, node))->key)
//#define rb_key(p) ((struct mynode_s *)((char *)(p) - (char *)(&(((struct mynode_s *)0)->node))))->key
//#define rb_key(ptr) ((mynode *)(ptr))->key
//#define rb_key(ptr) (ptr)->key

#define rb_key(x) ((bwlib_rb_entry((x), mynode, node))->key)

void dfs(bwlib_rb_node_t *root);
bwlib_rb_node_t *rb_lookup(bwlib_rb_root_t *root, int key);
int rb_insert(bwlib_rb_root_t *root, bwlib_rb_node_t *node);
