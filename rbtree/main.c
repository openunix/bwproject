#include <stdio.h>
#include <malloc.h>
#include "test.h"
#include "../bwlib.h"
#define N 10
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
		m = (mynode *)malloc(sizeof(mynode));
		m->key = i;
		p = m->node;
		rb_insert(&r, p);
	}

	printf("first: %d, last: %d\n", rb_key(bwlib_rb_first(&r)), rb_key(bwlib_rb_last(&r)));
	printf("second: %d, second last: %d\n", rb_key(bwlib_rb_next(bwlib_rb_first(&r))), rb_key(bwlib_rb_prev(bwlib_rb_last(&r))));
//	for (i = 1; i <= N; i++) {
		//p = rb_lookup(&r, i);
		//printf("%d\n", p->key);
		//bwlib_rb_erase(p, &r);
		//dfs(r.root_node); 
		//printf("\n");
		//printf("%d\n", bwlib_rb_entry(p, mynode, node)->key);
//	}
	return 0;
}
