
/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * mynode.c - This file realize the funcations for rbtree test ,it can be used as an example 
 * .
 * 
 * 
 * Dependencies:
 * mynode.h
 * Rbtree.h
 * bwoss_iface.h
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
#include "mynode.h"
#include "..\..\..\rbtree\Rbtree.h"
#include "..\..\..\bwoss\bwoss_iface.h"


struct nodetype *bwosl_node_search(bwlib_rb_root_t *root, unsigned long key)
{
	bwlib_rb_node_t *node = root->rb_node;
	
	while (!node) {
		struct nodetype *data = container_of(node, struct nodetype, node);
		int result;
		
		result = key - data->key;
		
		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

int bwosl_node_insert(bwlib_rb_root_t *root, struct nodetype *data)
{
    bwlib_rb_node_t **_new = &(root->rb_node);
	// bwlib_rb_node_t *parent = NULL;
	bwlib_rb_node_t *parent = NULL;
	
	//figure out where to put new node 
	while (*_new) {
		
		struct nodetype * _this = container_of(*_new, struct nodetype, node );
		int result = (data->key) - (_this->key);
		
		parent = *(_new);
		if (result < 0)
			_new = &((*(_new))->rb_left);
		else if (result > 0)
			_new = &((*(_new))->rb_right);
		else
			return 0;
	}
	
	// Add new node and rebalance tree. 
	bwlib_rb_link_node(&(data->node), parent, _new);
	bwlib_rb_insert_color(&(data->node), root);
	
	return 1;
	
}
  
int  bwosl_node_delete(bwlib_rb_root_t *root, unsigned long key)
{
	struct nodetype *data = bwosl_node_search(root, key);
	if (data) {
		
		bwlib_rb_erase(&(data->node), root);
		bwoss_free(data);
		return 1;
	}
	else
		return 0;
	
}