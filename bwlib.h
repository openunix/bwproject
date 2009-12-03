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
}bwlib_rb_node_t;

typedef struct bwlib_rb_root{
	/* TODO: Add the define of rb root node here */
}bwlib_rb_root_t;

extern void bwlib_rb_insert_color(bwlib_rb_node_t *, bwlib_rb_root_t *);
extern void bwlib_rb_erase(bwlib_rb_node_t *, bwlib_rb_root_t *);
extern void bwlib_rb_clear_node(bwlib_rb_node_t *);
extern bwlib_rb_node_t *bwlib_rb_first(bwlib_rb_root_t *);
extern bwlib_rb_node_t *bwlib_rb_last(bwlib_rb_root_t *);
extern bwlib_rb_node_t *bwlib_rb_next(bwlib_rb_node_t *)
extern bwlib_rb_node_t *bwlib_rb_prev(bwlib_rb_node_t *)
extern void bwlib_rb_link_node(bwlib_rb_node_t *, bwlib_rb_node_t *,
			       bwlib_rb_node_t **)

/* TODO: Fix the two utility macro define here */
#define bwlib_rb_enty(ptr, type, member)
#define BWLIB_RB_ROOT

/* 
 * TODO: Add the radix tree define here.
 */



#endif /* _BWLIB_H */

