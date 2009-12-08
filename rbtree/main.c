#include <stdio.h>
#include <malloc.h>
#include "test.h"
#include "../bwlib.h"
#define N 1024*1024
#define KEY_EXIST -3

int main()
{
	int i;
	mynode *m;
	bwlib_rb_node_t *p;
	bwlib_rb_root_t r = BWLIB_RB_ROOT;
	bwlib_rb_root_t *root = &r;
	bwlib_rb_init(root);
	printf("%x\n", root->root_node);

	for (i = 1; i <= N; i++) {
	//	printf("%d\n", i);
	//	m = (mynode *)malloc(sizeof(mynode));
	//	m->key = i;
		p = (bwlib_rb_node_t *)malloc(sizeof(bwlib_rb_node_t));
	//	m->node = p;
		p->key = i;
		rb_insert(&r, p);
	}

	for (i = 1; i <= N; i++) {
		//p = rb_lookup(&r, i);
		//printf("%d\n", p->key);
		//bwlib_rb_erase(p, &r);
		//dfs(r.root_node); 
		//printf("\n");
		//printf("%d\n", bwlib_rb_entry(p, mynode, node)->key);
	}
	return 0;
}
