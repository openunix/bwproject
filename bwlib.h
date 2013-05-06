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

#ifndef _BWLIB_H
#define _BWLIB_H

/* 
 * Attention: We wouldn't include any bwoss layer header here. Do this
 * in your private header file!
 */

typedef struct bwlib_rb_node{
	/* TODO: Add the define of rb node here */
	unsigned long parent;
	struct bwlib_rb_node *rb_left, *rb_right;
}bwlib_rb_node_t;

typedef struct bwlib_rb_root{
	/* TODO: Add the define of rb root node here */
	bwlib_rb_node_t *rb_node;	
}bwlib_rb_root_t;

typedef unsigned int uint32_t;

extern void bwlib_rb_init(bwlib_rb_root_t *);
extern void bwlib_rb_insert_color(bwlib_rb_node_t *, bwlib_rb_root_t *);
extern void bwlib_rb_erase(bwlib_rb_node_t *, bwlib_rb_root_t *);
extern void bwlib_rb_clear_node(bwlib_rb_node_t *);
extern bwlib_rb_node_t *bwlib_rb_first(bwlib_rb_root_t *);
extern bwlib_rb_node_t *bwlib_rb_last(bwlib_rb_root_t *);
extern bwlib_rb_node_t *bwlib_rb_next(bwlib_rb_node_t *);
extern bwlib_rb_node_t *bwlib_rb_prev(bwlib_rb_node_t *);
extern void bwlib_rb_link_node(bwlib_rb_node_t *, bwlib_rb_node_t *,
			       bwlib_rb_node_t **);

/* TODO: Fix the two utility macro define here */
#define bwlib_rb_entry(ptr, type, member)  ((type *)((char *)ptr - (char *)(&((type *)0)->member)))
#define BWLIB_RB_ROOT (struct bwlib_rb_root){NULL,}


#define RADIX_TREE_MAP_SHIFT	6	
#define RADIX_TREE_MAP_SIZE	(1UL << RADIX_TREE_MAP_SHIFT) /*It represents the number of slots.*/
#define RADIX_TREE_MAP_MASK	(RADIX_TREE_MAP_SIZE-1)  /*it is used to caculate the index of each level*/
#define RADIX_TREE_SUCCESS 0
#define RADIX_TREE_FAILED 1

typedef struct bwlib_radix_tree_node 
{
	uint32_t	height;		
	uint32_t	count;					 /*the number of slots which are not empty*/
	void		*slots[RADIX_TREE_MAP_SIZE]; 
}bwlib_radix_tree_node ;

typedef struct bwlib_radix_tree_root 
{
	uint32_t		height;
	struct bwlib_radix_tree_node	*rnode;
}bwlib_radix_tree_root;

void bwlib_radix_tree_init(bwlib_radix_tree_root*);
extern uint32_t bwlib_radix_tree_insert(bwlib_radix_tree_root *, uint32_t, void *);
extern void* bwlib_radix_tree_lookup(bwlib_radix_tree_root *, uint32_t);
extern void* bwlib_radix_tree_delete(bwlib_radix_tree_root *, uint32_t);


#pragma pack(pop)

#endif /* LSI_MEGA_SWR_COMMON_DEFS_H */

/* vim: set ts=4 sw=4 nowrap: */
