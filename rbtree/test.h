#include <stdio.h>
#include "../bwlib.h"
#include "rbtree.h"

#define rb_key(x) ((x)->key)

extern null_node;
typedef struct mynode
{
	int key;
	bwlib_rb_node_t *node;
}mynode;

void dfs(bwlib_rb_node_t *root);
bwlib_rb_node_t *rb_lookup(bwlib_rb_root_t *root, int key);
int rb_insert(bwlib_rb_root_t *root, bwlib_rb_node_t *node);
