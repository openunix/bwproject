#if !defined radix_tree_H
#define radix_tree_H

#include "../bwlib.h"
uint32_t bwlib_radix_tree_maxindex(uint32_t );
uint32_t bwlib_radix_tree_extend(bwlib_radix_tree_root *, uint32_t );
void bwlib_radix_tree_node_init(bwlib_radix_tree_node*);
#endif