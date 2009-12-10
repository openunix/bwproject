#include <stdio.h>
#include <malloc.h>
#include "test.h"
#include "../bwlib.h"
#define N 1024*1024*64
#define KEY_EXIST -3

int main()
{
	int i;
	mynode *m;
	bwlib_rb_node_t *p;
//	bwlib_rb_root_t r = BWLIB_RB_ROOT;
	bwlib_rb_root_t r;
	bwlib_rb_root_t *root = &r;
	bwlib_rb_init(root);
/*	printf("%x\n", root->root_node); */

	for (i = 1; i <= N; i++) {
	//	printf("%d\n", i);
	//	m = (mynode *)malloc(sizeof(mynode));
	//	m->key = i;
		p = (bwlib_rb_node_t *)malloc(sizeof(bwlib_rb_node_t));
	//	m->node = p;
		p->key = rand();
		rb_insert(&r, p);
	//	dfs(r.root_node);
		//printf("\n"); 
	}

	printf("first: %d, last: %d\n", rb_key(bwlib_rb_first(&r)), rb_key(bwlib_rb_last(&r)));
	printf("second: %d, second last: %d\n", rb_key(bwlib_rb_next(bwlib_rb_first(&r))), rb_key(bwlib_rb_prev(bwlib_rb_last(&r))));
#if 0
	for (i = 1; i <= N; i++) {
	//	printf("%d\n", i); 
		p = rb_lookup(&r, N-i);
		//printf("\n%d\n", p->key); 
		if (!is_null_node(p)) {
			bwlib_rb_erase(p, &r);
			free(p);
		}
		dfs(r.root_node); 
		/* printf("%d\n", bwlib_rb_entry(p, mynode, node)->key); */
	//	printf("\n"); 
	} 
#endif
	return 0;
}
