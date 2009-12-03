/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * bwlib_wrapper.h - A wrap-layer of bwlib in Linux Kernel
 * 
 * Author:       Feng Shuo
 * Dependencies: linux/rbtree.h
 *
 * ChangeLog:
 *  2009-12-2 Initial Created
 * ToDo:
 *  None
 */

#ifndef _BWLIB_WRAPPER_H
#define _BWLIB_WRAPPER_H

#include <linux/autoconf.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/rbtree.h>

#include <linux/fs.h>

/* bwoss_iface.h */
typedef spinlock_t bwoss_spinlock_t;
typedef unsigned long bwoss_irql_t;
static inline void bwoss_spin_lock(bwoss_spinlock_t *l)
{
	spin_lock(l);
}
static inline void bwoss_spin_unlock(bwoss_spinlock_t *l)
{
	spin_unlock(l);
}
static inline void bwoss_spin_lock_irqsave(bwoss_spinlock_t *l, bwoss_irql_t *f)
{
	spin_lock_irqsave(l, *f);
}
static inline void bwoss_spin_unlock_irqrestore(bwoss_spinlock_t *l, bwoss_irql_t f)
{
	spin_unlock_irqrestore(l, f);
}
static inline void bwoss_spin_lock_init(bwoss_spinlock_t *l)
{
	spin_lock_init(l);
}
static inline void *bwoss_malloc(uint32_t size)
{
	return kmalloc(size, GFP_KERNEL);
}
static inline void *bwoss_zalloc(uint32_t size)
{
	return kzalloc(size, GFP_KERNEL);
}

/* rbtree.h */
typedef struct rb_node bwlib_rb_node_t;
typedef struct rb_root bwlib_rb_root_t;

static inline void bwlib_rb_insert_color(bwlib_rb_node_t *n, bwlib_rb_root_t *r)
{
	rb_insert_color(n, r);
}
static inline void bwlib_rb_erase(bwlib_rb_node_t *n, bwlib_rb_root_t *r)
{
	rb_erase(n, r);
}
static inline void bwlib_rb_clear_node(bwlib_rb_node_t *n)
{
	RB_CLEAR_NODE(n);
}
static inline bwlib_rb_node_t *bwlib_rb_first(bwlib_rb_root_t *r)
{
	return rb_first(r);
}
static inline bwlib_rb_node_t *bwlib_rb_last(bwlib_rb_root_t *r)
{
	return rb_last(r);
}
static inline bwlib_rb_node_t *bwlib_rb_next(bwlib_rb_node_t *r)
{
	return rb_next(r);
}
static inline bwlib_rb_node_t *bwlib_rb_prev(bwlib_rb_node_t *r)
{
	return rb_prev(r);
}
static inline void bwlib_rb_link_node(bwlib_rb_node_t *node,
				      bwlib_rb_node_t *parent,
				      bwlib_rb_node_t **rb_link)
{
	return rb_link_node(node, parent, rb_link);
}
#define bwlib_rb_entry(ptr, type, member) rb_entry(ptr, type, member)
#define BWLIB_RB_ROOT ((bwlib_rb_root_t)RB_ROOT)

#endif	/* _BWLIB_WRAPPER_H */
