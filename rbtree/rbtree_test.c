/**************************************/
/* Author:mahongyuan@nrchpc.ac.cn     */
/* Insert node in order then          */
/* search the node which was inserted */
/**************************************/

/**************************************/
#include "bwlib.h"

/*Should provided by bwoss...*/
#include <stdio.h>
#include <malloc.h>

/*************************************/
#define NODE_NUM 1000000
#define TRUE     1
#define FALSE    0
/**************************************/
struct perf_node{
	struct bwlib_rb_node node;
	int key;
};
struct bwlib_rb_root perf_tree_root = RB_ROOT;

/**************************************/

static struct perf_node *search_node(struct bwlib_rb_root *root, int key)
{
	struct bwlib_rb_node *node = root->bwlib_rb_node;

	while (node) {
		struct perf_node *data = container_of(node, struct perf_node, node);

		if (key < data->key)
			node = node->rb_left;
		else if (key > data->key)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

static int insert_node(struct bwlib_rb_root *root, struct perf_node *data)
{
	struct bwlib_rb_node **new = &(root->bwlib_rb_node), *parent = NULL;

	while (*new) {
		struct perf_node *this = container_of(*new, struct perf_node, node);

		parent = *new;
		if (data->key < this->key)
			new = &((*new)->rb_left);
		else if (data->key > this->key)
			new = &((*new)->rb_right);
		else
			return FALSE;
	}

	bwlib_rb_link_node(&data->node, parent, new);
	bwlib_rb_insert_color(&data->node, root);

	return TRUE;
}

static int delete_node(struct bwlib_rb_root *root, int key)
{
	struct perf_node *data = search_node(root, key);

	if (data) {
		bwlib_rb_erase(&data->node, root);
		free(data);
		return TRUE;
	} else { 
		fprintf(stderr, "The node which want to delete is not in the tree:(\n");
		return FALSE;
	}
}

static void traverse_tree(struct bwlib_rb_root * root)

{
	struct bwlib_rb_node *node;
	int tmp = 0;
	for (node = bwlib_rb_first(root); node; node = bwlib_rb_next(node)){
		tmp++;
	}              
}

static void back_traverse_tree(struct bwlib_rb_root * root)
{
	struct bwlib_rb_node *node;
	int tmp = 0;
	for (node = bwlib_rb_last(root); node; node = bwlib_rb_prev(node)){
		tmp++;
	}
}

int main(int argc, char** argv)
{
	int i;
	struct perf_node *data;

	fprintf(stderr, "Inserting %d nodes which range from 1 to %d into rbtree......\n", NODE_NUM, NODE_NUM);
	/**************insert**************/
	for(i = 1; i < NODE_NUM; i++){
		if(!(data = malloc(sizeof(struct perf_node)))) {
			fprintf(stderr, "%s: NoMem\n", __func__);
			return 0;
		}
		data->key = i;
		insert_node(&perf_tree_root, data);
	}       
	/**************search**************/
	for(i = 1; i < NODE_NUM; i++){
		data = search_node(&perf_tree_root, i);
		if(!data)
			fprintf(stderr, "%s: BUG!\n", __func__); 
	}
	/**************traverse************/
	traverse_tree(&perf_tree_root);
	/*********back-traverse************/
	back_traverse_tree(&perf_tree_root);
	for(i = 1; i < NODE_NUM; i++){
		delete_node(&perf_tree_root, i);
	}

	return 0;
}
