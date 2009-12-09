#ifndef RB_TREE
#define RB_TREE

#include <stdio.h>
#include <assert.h>
#include "rbtree.h"
#include "../bwlib.h"

bwlib_rb_node_t null_node = {
	0,NULL,NULL
};

void rb_set_parent(bwlib_rb_node_t *node, bwlib_rb_node_t *p)
{
	node->parent  =  (node->parent & 3) | (unsigned long)(p);
}

extern int bwlib_rb_init(bwlib_rb_root_t *root)
{
	/* 
	 * init a rbtree root, make it root_node point to the global null_node 
	 * and now the tree have no data node 
	 */
	if (!root) {
		return EMPTY_ROOT;
	}
	
	root->root_node = &null_node; 
	printf("rb init begin %x\n", root->root_node);
	rb_set_parent(&null_node, &null_node); 
	rb_set_black(&null_node);
	null_node.rb_left = null_node.rb_right = &null_node;
	printf("rb init\n");
}

static bwlib_rb_node_t *rb_minmum(bwlib_rb_node_t *cur)
{
	bwlib_rb_node_t *p = cur;
	while (!is_null_node(p->rb_left)) {
		p = p->rb_left;
	}

	return p;
}

static bwlib_rb_node_t *rb_maxmum(bwlib_rb_node_t *cur)
{
	bwlib_rb_node_t *p = cur;
	while (!is_null_node(cur->rb_right)) {
		p = p->rb_right;
	}

	return p;
}

extern bwlib_rb_node_t *bwlib_rb_next(bwlib_rb_node_t *cur)
{
	bwlib_rb_node_t *p = cur;
	if (!is_null_node(cur->rb_right)) {
		return rb_minmum(cur->rb_right); 
	}
	
	p = rb_parent(p);
	while ( !is_null_node(p) && p == rb_parent(p)->rb_right ) {
		p = rb_parent(p);		
	}
	
	return p;
}

extern bwlib_rb_node_t *bwlib_rb_prev(bwlib_rb_node_t *cur)
{
	bwlib_rb_node_t *p = cur;
	if (!is_null_node(cur->rb_left)) {
		return rb_minmum(cur->rb_left); 
	}
	
	p = rb_parent(p);
	while ( !is_null_node(p) && p == rb_parent(p)->rb_left) {
		p = rb_parent(p);		
	}
	
	return p;
}

extern bwlib_rb_node_t *bwlib_rb_first(bwlib_rb_root_t *root)
{
	bwlib_rb_node_t	*n;

	n = root->root_node;
	if (is_null_node(n))
		return &null_node;
	while (!is_null_node(n->rb_left))
		n = n->rb_left;
	return n;
}

extern bwlib_rb_node_t *bwlib_rb_last(bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *n;
	n = root->root_node;
	if (is_null_node(n))
		return &null_node;
	while (!is_null_node(n->rb_right))
		n = n->rb_right;
	return n;

}

static void rb_left_rotate(bwlib_rb_root_t *root, bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *x, *y;
	x = node; 
	y = x->rb_right;

	x->rb_right = y->rb_left;
	if (!is_null_node(y->rb_left)) {
		rb_set_parent(y->rb_left, x);
	}
	rb_set_parent(y, rb_parent(x));
	
	if(is_null_node(rb_parent(x))) {
		root->root_node = y;
	} else {
		if (x == rb_parent(x)->rb_left) {
			rb_parent(x)->rb_left = y;
		} else {
			rb_parent(x)->rb_right = y;
		}
	}
	y->rb_left = x;
	rb_set_parent(x, y);
}

static void rb_right_rotate(bwlib_rb_root_t *root, bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *y, *x;
	x = node;
	y = x->rb_left;

	x->rb_left = y->rb_right;
	if (!is_null_node(y->rb_right)) {
		rb_set_parent(y->rb_right, x);
	}
	rb_set_parent(y, rb_parent(x));

	if (is_null_node(rb_parent(x))) {
		root->root_node = y;
	} else {
		if (x == rb_parent(x)->rb_right) {
			rb_parent(x)->rb_right = y;
		} else {
			rb_parent(x)->rb_left = y;
		}
	}

	y->rb_right = x;
	rb_set_parent(x, y);
}


void bwlib_rb_insert_color(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *x, *y;
	x = node; y = rb_parent(rb_parent(x));
	assert(!is_null_node(y));
	while (rb_is_red(rb_parent(x))) {
		if (rb_parent(x) == rb_parent(rb_parent(x))->rb_left) {	
			/* x's father  is grandfather's left child */
			y = rb_parent(rb_parent(x))->rb_right;	/* y is x's uncle node */
			if (rb_is_red(y)) {	/* y is red */
				rb_set_black(y);
				rb_set_black(rb_parent(x));
				/* rb_set_red(rb_parent(rb_parent(x))); */
				rb_set_red(rb_parent(rb_parent(x)));
				x = rb_parent(rb_parent(x));
			} else {	/* y is black */
				if (x == rb_parent(x)->rb_right) {
					x = rb_parent(x);
					rb_left_rotate(root, x);
				} 
				rb_set_red(rb_parent(rb_parent(x)));
				rb_set_black(rb_parent(x));
				rb_right_rotate(root, rb_parent(rb_parent(x)));
				/* x = rb_parent(x); */
			}
		} else {
		/* x's father  is grandfather's right child */
			y = y->rb_left;
			if (rb_is_red(y)) {	/* y is red */
				rb_set_black(y);
				rb_set_black(rb_parent(x));
				rb_set_red(rb_parent(rb_parent(x)));
				x = rb_parent(rb_parent(x));
			} else {	/* y is black */
				if (x == rb_parent(x)->rb_left) {
					x = rb_parent(x);
					rb_right_rotate(root, x);
				} 
				rb_set_red(rb_parent(rb_parent(x)));
				rb_set_black(rb_parent(x));
				rb_left_rotate(root, rb_parent(rb_parent(x)));
			}
		}
	}
	rb_set_black(root->root_node);
}

extern void bwlib_rb_link_node(bwlib_rb_node_t *node, bwlib_rb_node_t *parent, bwlib_rb_node_t **link)
{
	rb_set_parent(node, parent);
	node->rb_left = node->rb_right = &null_node;
	*link = node;
}

/* int rb_insert(bwlib_rb_root_t *root, bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *p, *pp;
	int key = node->key;

	if (is_null_node(root->root_node)) {
		root->root_node = node;
		node->rb_left = node->rb_right = &null_node;
		rb_set_parent(node, &null_node);
		rb_set_black(node);
		return 0;
	}	

	p = root->root_node;
	pp = &null_node;
	while (!is_null_node(p)) {
		pp = p;
		if (key == p->key) {
			return KEY_EXIST;
		}
		if ( key < p->key) {
			p = p->rb_left;
		} else {
			p = p->rb_right;
		}
	}
	
	if (key < pp->key) {
		pp->rb_left = node;
	} else {
		pp->rb_right = node;
	}

	node->rb_left = node->rb_right = &null_node;
	rb_set_parent(node, pp); 
	rb_set_red(node);
	if (rb_is_red(pp))
		bwlib_rb_insert_color(root, node); 
	return 0;
} */

static int rb_delete_fixup(bwlib_rb_root_t *root, bwlib_rb_node_t *node) 
{
	bwlib_rb_node_t *x, *w;
	x = node; 
	while (x != root->root_node && rb_is_black(x)) {
		if (x == rb_parent(x)->rb_left) {	/* x is parent's left child */
			w = rb_parent(x)->rb_right;		/* w is x's borther node */
			if (rb_is_red(w)) {	/* w is red color node */
				rb_set_black(w);
				rb_set_red(rb_parent(x));
				rb_left_rotate(root, rb_parent(x));
				w = rb_parent(x)->rb_right;
			} 
			/* w is black node */
			if (rb_is_black(w->rb_left) && rb_is_black(w->rb_right)) {
				rb_set_red(w);
				x = rb_parent(x);
			} else {
				/* one of w's child is not black */
				if (rb_is_black(w->rb_right)) {
					rb_set_black(w->rb_left);
					rb_set_red(w);
					rb_right_rotate(root, w);
					w = rb_parent(x)->rb_right;
				} 
				/* now w's right child is red */
				if (rb_is_red(rb_parent(x))) {
					rb_set_red(w);
				} else {
					rb_set_black(w);
				}
				rb_set_black(rb_parent(x));
				rb_set_black(w->rb_right);
				rb_left_rotate(root, rb_parent(x));
				x = root->root_node;
			}
		} else {	/* x is parent's rihgt child */
			w = rb_parent(x)->rb_left;
			if (rb_is_red(w)) {	/* w is red color node */
				rb_set_black(w);
				rb_set_red(rb_parent(x));
				rb_right_rotate(root, rb_parent(x));
				w = rb_parent(x)->rb_left;
			} 
			/* w is black node */
			if (rb_is_black(w->rb_right) && rb_is_black(w->rb_left)) {
				rb_set_red(w);
				x = rb_parent(x);
			} else {
				/* one of w's child is not black */
				if (rb_is_black(w->rb_left)) {
					rb_set_black(w->rb_right);
					rb_set_red(w);
					rb_left_rotate(root, w);
					w = rb_parent(x)->rb_left;
				} 
				/* now w's right child is red */
				if (rb_is_red(rb_parent(x))) {
					rb_set_red(w);
				} else {
					rb_set_black(w);
				}
				rb_set_black(rb_parent(x));
				rb_set_black(w->rb_left);
				rb_right_rotate(root, rb_parent(x));
				x = root->root_node;
			}
		}
	}
	rb_set_black(x);
}

void bwlib_rb_erase(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *p, *d, *old;
	int f = 0;
	
	old = node;
	assert(!is_null_node(node));
	if (is_null_node(node->rb_left) || is_null_node(node->rb_right)) {
		p = node;	
	} else {
		p = bwlib_rb_next(node);
	}

	if (!is_null_node(p->rb_left)) {
		d = p->rb_left;
	} else {
		d = p->rb_right;
	}
	/* if (!is_null_node(d)) */
	rb_set_parent(d, rb_parent(p));
	
	if (is_null_node(rb_parent(p))) {
		root->root_node = d;
	} else {
		if (p == rb_parent(p)->rb_right) {
			rb_parent(p)->rb_right = d;
		} else {
			rb_parent(p)->rb_left = d;
		}
	}

	if (rb_is_black(p)) {
		f = 1;
	} else 
		f = 0;

	if (p != node) {
		/* copy the date area to the new node */
		p->parent = old->parent;
		p->rb_left = old->rb_left;
		p->rb_right = old->rb_right;
		
		if (!is_null_node(rb_parent(old))) {
			if (old ==  rb_parent(old)->rb_left) {
				rb_parent(old)->rb_left = p;
			} else {
				rb_parent(old)->rb_right = p;
			}
		} else 
			root->root_node = p;

		rb_set_parent(old->rb_left, p);
		if (!is_null_node(old->rb_right)) {
			rb_set_parent(old->rb_right, p);
		}
	}

	if (f) {
		rb_delete_fixup(root, d);
	}
}

extern void bwlib_rb_clear_node(bwlib_rb_node_t *node)
{
}

#endif
