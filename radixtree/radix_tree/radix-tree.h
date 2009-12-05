#if !defined radix_tree_H
#define radix_tree_H


#define RADIX_TREE_MAP_SHIFT	6	
#define RADIX_TREE_MAP_SIZE	(1UL << RADIX_TREE_MAP_SHIFT) /*It represents the number of slots.*/
#define RADIX_TREE_MAP_MASK	(RADIX_TREE_MAP_SIZE-1)       /*it is used to caculate the index of each level*/
#define RADIX_TREE_SUCCESS 0
#define RADIX_TREE_FAILED 1

typedef int uint32_t;
typedef struct radix_tree_node 
{
	uint32_t	height;		
	uint32_t	count;                                /*the number of slots which are not empty*/
	void		*slots[RADIX_TREE_MAP_SIZE]; 
}radix_tree_node;

typedef struct radix_tree_root 
{
	uint32_t		height;
	struct radix_tree_node	*rnode;
}radix_tree_root;

uint32_t bwlib_radix_tree_maxindex(uint32_t );
uint32_t bwlib_radix_tree_extend(struct radix_tree_root *, uint32_t );
void bwlib_radix_tree_node_init(radix_tree_node*);

void bwlib_radix_tree_init(radix_tree_root* root);
uint32_t bwlib_radix_tree_insert(struct radix_tree_root *, uint32_t, void *);
void* bwlib_radix_tree_lookup(struct radix_tree_root *, uint32_t);
void* bwlib_radix_tree_delete(struct radix_tree_root *, uint32_t);
#endif