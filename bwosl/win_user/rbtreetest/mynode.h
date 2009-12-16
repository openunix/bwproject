/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * mynode.h - This file contains all the function prototypes
 * that are exported by mynode for test cases.
 * 
 * 
 * Dependencies:
 * None
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
#ifndef _MYNODE_H
#define _MYNODE_H

#include "..\..\..\bwlib.h"

#define is_null_node(x) ((x) == &null_node)
struct nodetype {
	bwlib_rb_node_t node;
	unsigned long key;
	//char *keystring;
};



struct nodetype* bwosl_node_search(bwlib_rb_root_t *root, unsigned long key);
int bwosl_node_insert(bwlib_rb_root_t *root, struct nodetype *data);
int  bwosl_node_delete(bwlib_rb_root_t *root, unsigned long key);

#endif