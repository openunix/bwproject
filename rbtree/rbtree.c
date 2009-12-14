#ifndef RB_TREE
#define RB_TREE

#include <stdio.h>
#include <assert.h>
#include "rbtree.h"

static void rb_left_rotate(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *right = node->rb_right;
	bwlib_rb_node_t *parent = rb_parent(node);

	if ((node->rb_right = right->rb_left))
		rb_set_parent(right->rb_left, node);
	right->rb_left = node;

	rb_set_parent(right, parent);

	if (parent)
	{
		if (node == parent->rb_left)
			parent->rb_left = right;
		else
			parent->rb_right = right;
	}
	else
		root->root_node = right;
	rb_set_parent(node, right);
}

static void rb_right_rotate(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *left = node->rb_left;
	bwlib_rb_node_t *parent = rb_parent(node);

	if ((node->rb_left = left->rb_right))
		rb_set_parent(left->rb_right, node);
	left->rb_right = node;

	rb_set_parent(left, parent);

	if (parent)
	{
		if (node == parent->rb_right)
			parent->rb_right = left;
		else
			parent->rb_left = left;
	}
	else
		root->root_node = left;
	rb_set_parent(node, left);
}

void bwlib_rb_insert_color(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *parent, *gparent;

	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		if (parent == gparent->rb_left)
		{
			{
				bwlib_rb_node_t *uncle = gparent->rb_right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			if (parent->rb_right == node)
			{
				bwlib_rb_node_t *tmp;
				rb_left_rotate(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			rb_right_rotate(gparent, root);
		} else {
			{
				bwlib_rb_node_t *uncle = gparent->rb_left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			if (parent->rb_left == node)
			{
				bwlib_rb_node_t *tmp;
				rb_right_rotate(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			rb_left_rotate(gparent, root);
		}
	}

	rb_set_black(root->root_node);
}

static void __rb_erase_color(bwlib_rb_node_t *node, bwlib_rb_node_t *parent,
			     bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *other;

	while ((!node || rb_is_black(node)) && node != root->root_node)
	{
		if (parent->rb_left == node)
		{
			other = parent->rb_right;
			if (rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				rb_left_rotate(parent, root);
				other = parent->rb_right;
			}
			if ((!other->rb_left || rb_is_black(other->rb_left)) &&
			    (!other->rb_right || rb_is_black(other->rb_right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->rb_right || rb_is_black(other->rb_right))
				{
					bwlib_rb_node_t *o_left;
					if ((o_left = other->rb_left))
						rb_set_black(o_left);
					rb_set_red(other);
					rb_right_rotate(other, root);
					other = parent->rb_right;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				if (other->rb_right)
					rb_set_black(other->rb_right);
				rb_left_rotate(parent, root);
				node = root->root_node;
				break;
			}
		}
		else
		{
			other = parent->rb_left;
			if (rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				rb_right_rotate(parent, root);
				other = parent->rb_left;
			}
			if ((!other->rb_left || rb_is_black(other->rb_left)) &&
			    (!other->rb_right || rb_is_black(other->rb_right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->rb_left || rb_is_black(other->rb_left))
				{
					bwlib_rb_node_t *o_right;
					if ((o_right = other->rb_right))
						rb_set_black(o_right);
					rb_set_red(other);
					rb_left_rotate(other, root);
					other = parent->rb_left;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				if (other->rb_left)
					rb_set_black(other->rb_left);
				rb_right_rotate(parent, root);
				node = root->root_node;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}

void bwlib_rb_erase(bwlib_rb_node_t *node, bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *child, *parent;
	int color;

	if (!node->rb_left)
		child = node->rb_right;
	else if (!node->rb_right)
		child = node->rb_left;
	else
	{
		bwlib_rb_node_t *old = node, *left;

		node = node->rb_right;
		while ((left = node->rb_left) != NULL)
			node = left;
		child = node->rb_right;
		parent = rb_parent(node);
		color = rb_color(node);

		if (child)
			rb_set_parent(child, parent);
		if (parent == old) {
			parent->rb_right = child;
			parent = node;
		} else
			parent->rb_left = child;

		node->parent = old->parent;
		node->rb_right = old->rb_right;
		node->rb_left = old->rb_left;

		if (rb_parent(old))
		{
			if (rb_parent(old)->rb_left == old)
				rb_parent(old)->rb_left = node;
			else
				rb_parent(old)->rb_right = node;
		} else
			root->root_node = node;

		rb_set_parent(old->rb_left, node);
		if (old->rb_right)
			rb_set_parent(old->rb_right, node);
		goto color;
	}

	parent = rb_parent(node);
	color = rb_color(node);

	if (child)
		rb_set_parent(child, parent);
	if (parent)
	{
		if (parent->rb_left == node)
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->root_node = child;

 color:
	if (color == RB_BLACK)
		__rb_erase_color(child, parent, root);
}

/*
 * This function returns the first node (in sort order) of the tree.
 */
extern bwlib_rb_node_t *bwlib_rb_first(bwlib_rb_root_t *root)
{
	bwlib_rb_node_t	*n;

	n = root->root_node;
	if (!n)
		return NULL;
	while (n->rb_left)
		n = n->rb_left;
	return n;
}

extern bwlib_rb_node_t *bwlib_rb_last(bwlib_rb_root_t *root)
{
	bwlib_rb_node_t	*n;

	n = root->root_node;
	if (!n)
		return NULL;
	while (n->rb_right)
		n = n->rb_right;
	return n;
}

extern bwlib_rb_node_t *bwlib_rb_next(bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *parent;

	if (rb_parent(node) == node)
		return NULL;

	/* If we have a right-hand child, go down and then left as far
	   as we can. */
	if (node->rb_right) {
		node = node->rb_right; 
		while (node->rb_left)
			node=node->rb_left;
		return (bwlib_rb_node_t *)node;
	}

	/* No right-hand children.  Everything down and left is
	   smaller than us, so any 'next' node must be in the general
	   direction of our parent. Go up the tree; any time the
	   ancestor is a right-hand child of its parent, keep going
	   up. First time it's a left-hand child of its parent, said
	   parent is our 'next' node. */
	while ((parent = rb_parent(node)) && node == parent->rb_right)
		node = parent;

	return parent;
}

extern bwlib_rb_node_t *bwlib_rb_prev(bwlib_rb_node_t *node)
{
	bwlib_rb_node_t *parent;

	if (rb_parent(node) == node)
		return NULL;

	/* If we have a left-hand child, go down and then right as far
	   as we can. */
	if (node->rb_left) {
		node = node->rb_left; 
		while (node->rb_right)
			node=node->rb_right;
		return (bwlib_rb_node_t *)node;
	}

	/* No left-hand children. Go up till we find an ancestor which
	   is a right-hand child of its parent */
	while ((parent = rb_parent(node)) && node == parent->rb_left)
		node = parent;

	return parent;
}

void rb_replace_node(bwlib_rb_node_t *victim, bwlib_rb_node_t *new,
		     bwlib_rb_root_t *root)
{
	bwlib_rb_node_t *parent = rb_parent(victim);

	/* Set the surrounding nodes to point to the replacement */
	if (parent) {
		if (victim == parent->rb_left)
			parent->rb_left = new;
		else
			parent->rb_right = new;
	} else {
		root->root_node = new;
	}
	if (victim->rb_left)
		rb_set_parent(victim->rb_left, new);
	if (victim->rb_right)
		rb_set_parent(victim->rb_right, new);

	/* Copy the pointers/colour from the victim to the replacement */
	*new = *victim;
}

void bwlib_rb_link_node(bwlib_rb_node_t * node, bwlib_rb_node_t * parent,
				bwlib_rb_node_t ** rb_link)
{
	node->parent= (unsigned long )parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}

#endif
