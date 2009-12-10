#include <stdio.h>
#include "test.h"
#include "../bwlib.h"
#include "rbtree.h"

int dfs(bwlib_rb_node_t *root)
{
	int bhl ,bhr, flag;
	if (!root) return 0;
	if (is_null_node(root))
		return 1;
	if (rb_is_black(root)) {
		flag = 1;
		//printf("%d_b ", rb_key(root));
	} else {
		flag = 0;
		//printf("%d_r ", rb_key(root)); 
	}

	if (!flag && rb_is_red(root->rb_left)) {
		printf("%d is red and %d is red\n", rb_key(root), rb_key(root->rb_left));
	} else {
		if (!flag && rb_is_red(root->rb_right)) {
			printf("%d is red and %d is red\n", rb_key(root), rb_key(root->rb_right));
		}
	}

	bhl = dfs(root->rb_left);
	bhr = dfs(root->rb_right);
	if (!bhl || !bhr) return 0;

	if (bhl != bhr) {
		printf("\n#############################\n%d bhl is not equal to bhr\n###############################\n", rb_key(root));
		return 0;
	} else 
		return bhl+flag;
}

bwlib_rb_node_t *rb_lookup(bwlib_rb_root_t *root, int key)
{
	bwlib_rb_node_t *p;
	int key0;
	p = root -> root_node;
	while (!is_null_node(p)) {
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

