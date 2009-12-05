#include "radix-tree.h"
#include "stdlib.h"
//#include "stdio.h"

uint32_t pow(uint32_t base,uint32_t exp)
{
	uint32_t result = base;
	uint32_t i = 0;
	for(i = 1; i< exp; i++)
		result *= base;
	return result;
}
/*
 function£º     Caculate maxindex from height
 paramer£º      height
 return value£º maxindex
*/
uint32_t bwlib_radix_tree_maxindex(uint32_t height)
{
	if(height<1) 
		return 0;
	else
		return pow(RADIX_TREE_MAP_SIZE,height) -1;
}

void bwlib_radix_tree_init(radix_tree_root* root)
{
	root->height = 0;
	root->rnode =NULL;
}
void bwlib_radix_tree_node_init(radix_tree_node* node)
{
		uint32_t i = 0;
		node->count = 0 ;
		node->height= 0 ;
		for( i=0 ; i<RADIX_TREE_MAP_SIZE; i++)
			node->slots[i]=NULL; 
}
/*
function£º extend the depth of the tree
need:      bwlib_radix_tree_maxindex
*/
uint32_t bwlib_radix_tree_extend(struct radix_tree_root *root, uint32_t index)
{
	struct radix_tree_node *node;
	uint32_t height;

	/* Figure out what the height should be.*/
	height = root->height + 1;              
	while (index > bwlib_radix_tree_maxindex(height))  
		height++;
	if (root->rnode == NULL) 
	{
		root->height = height;
		goto out;
	}

	do {
		uint32_t newheight;
		if (!(node =(radix_tree_node*) malloc(sizeof(radix_tree_node))))
			return RADIX_TREE_FAILED;
		bwlib_radix_tree_node_init(node);
		/* Increase the height.*/
		node->slots[0] = root->rnode;
		newheight = root->height+1;
		node->height = newheight;
		node->count = 1;
		root ->rnode = node;
		root->height = newheight;
	} while (height > root->height);
out:
	return RADIX_TREE_SUCCESS;
}

/*
bwlib_radix_tree_maxindex
bwlib_radix_tree_extend
*/
uint32_t bwlib_radix_tree_insert(struct radix_tree_root *root,
			uint32_t index, void *item)
{
	struct radix_tree_node *node = NULL, *slot;
	uint32_t height, shift;
	uint32_t offset;
	uint32_t error;

	/* Make sure the tree is high enough.*/
	if (index > bwlib_radix_tree_maxindex(root->height)) 
	{
		error = bwlib_radix_tree_extend(root, index);
		if (error)
		{
			return RADIX_TREE_FAILED;
		}
	}

	slot = root->rnode;
	height = root->height;
	shift = (height-1) * RADIX_TREE_MAP_SHIFT;

	offset = 0;			/* uninitialised var warning */
	while (height > 0) 
	{
		if (slot == NULL)  
		{
			/* Have to add a child node.*/
			if (!(slot = (radix_tree_node*)malloc(sizeof(struct radix_tree_node))))
			{
				/*printf("Memory Allocation failed!\n");*/
				return RADIX_TREE_FAILED;
			}
		    bwlib_radix_tree_node_init(slot);
			slot->height = height;
			if (node)   
			{
				node->slots[offset] = slot;
				node->count++;
			} 
			else
			     root->rnode =slot; 
		}
		/* Go a level down */
		offset = (index >> shift) & RADIX_TREE_MAP_MASK; 
		node = slot;
		slot =(radix_tree_node*) node->slots[offset];
		shift -= RADIX_TREE_MAP_SHIFT;
		height--;
	}

	if (slot != NULL) 
	{
	/*	printf("slot is null!\n");*/
		return 1;
	}
	if (node) 
	{
		node->count++;
		node->slots[offset] = item;
	} 
	else
	{
		root->rnode = (radix_tree_node*)item; 
	}

	return 0;
}

void* bwlib_radix_tree_lookup(struct radix_tree_root *root, uint32_t index)
{
	uint32_t height = root->height;
	uint32_t shift =0;
     if(height == 0)
		 return root->rnode;
	 else 
	 {
		 radix_tree_node * node =root->rnode;
		 while(height>0)
		 {
			 uint32_t offset =0;
			 shift = (height-1) * RADIX_TREE_MAP_SHIFT;
			 offset = (index >> shift) & RADIX_TREE_MAP_MASK;
			 node = (radix_tree_node*)node->slots[offset];
			 shift -= RADIX_TREE_MAP_SHIFT;
			 height --;
		 }
		 return node;
	 }	 
}

void* bwlib_radix_tree_delete(struct radix_tree_root *root, uint32_t index)
{
	uint32_t height = 0;
	uint32_t shift =0;
	if (index > bwlib_radix_tree_maxindex(root->height)) 
	return 0;
	height = root->height;
	
     if(height == 0)
	 {
		 root->rnode=NULL;
		 return root;
	 }
	 else 
	 {
		 radix_tree_node * node =root->rnode;
		 radix_tree_node * parent_node =NULL;
		 uint32_t offset =0;
		 while(height>0)
		 {
			 shift = (height-1) * RADIX_TREE_MAP_SHIFT;
			 offset = (index >> shift) & RADIX_TREE_MAP_MASK;
             parent_node = node;
			 node = (radix_tree_node*)node->slots[offset];
			 shift -= RADIX_TREE_MAP_SHIFT;
			 height --;
		 }
		 free(parent_node->slots[offset]);
		 parent_node->slots[offset]=NULL;
		 parent_node->count--;
		 return parent_node;
	 }	 
}



