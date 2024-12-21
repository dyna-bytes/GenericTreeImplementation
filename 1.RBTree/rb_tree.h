#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include <stddef.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

enum COLOR { RED, BLACK };

struct rb_node {
    unsigned int color;
    struct rb_node *parent;
    struct rb_node *right;
    struct rb_node *left;
};

struct rb_root {
	struct rb_node *rb_node;
};

struct rb_node *grandparent(struct rb_node *n);
struct rb_node *uncle(struct rb_node *n);

void is_root(struct rb_node *n);
void has_black_parent(struct rb_node *n);
void has_red_uncle_with_red_parent(struct rb_node *n);
void is_inside_descendant_with_red_parent_black_uncle(struct rb_node *n);
void is_outside_descendant_with_red_parent_black_uncle(struct rb_node *n);
#endif