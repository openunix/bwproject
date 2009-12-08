#include <stdio.h>
#include "test.h"
#include "../bwlib.h"
#include "rbtree.h"

void dfs(bwlib_rb_node_t *root)
{
	if (is_null_node(root))
		return;
	if (rb_is_black(root)) {
		printf("%d_b ", rb_key(root));
	} else {
		printf("%d_r ", rb_key(root));
	}

	if (!is_null_node(root->rb_left)) 
		dfs(root->rb_left);
	if (!is_null_node(root->rb_right))
		dfs(root->rb_right);
}

bwlib_rb_node_t *rb_lookup(bwlib_rb_root_t *root, int key)
{
	bwlib_rb_node_t *p;
	int key0;
	p = root -> root_node;
	while (!is_null_node(p)) {
		//key0 = bwlib_rb_entry(p, mynode, node)->key;
		key0 = rb_key(p);
		if ( key == key0) {
			break;
		}
		if ( key < key0 ) {
			p = p->rb_left;
		} else {
			p = p->rb_right;
		}
	}

	return p;
}

int rb_insert(bwlib_rb_root_t *root, bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *p, *pp;
	int key0;
//	int key = bwlib_rb_entry(node, mynode, node)->key;
	int key = rb_key(node);

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
		//key0 = bwlib_rb_entry(p, mynode, node)->key;
		key0 = rb_key(p);
		if (key == key0) {
			return KEY_EXIST;
		}
		if ( key < key0) {
			p = p->rb_left;
		} else {
			p = p->rb_right;
		}
	}
	
	//key0 = bwlib_rb_entry(pp, mynode, node)->key;
	key0 = rb_key(pp);
	if (key < key0) {
		pp->rb_left = node;
	} else {
		pp->rb_right = node;
	}

	node->rb_left = node->rb_right = &null_node;
	rb_set_parent(node, pp); 
	rb_set_red(node);
	if (rb_is_red(pp))
		bwlib_rb_insert_color(node, root); 
	return 0;
} 

