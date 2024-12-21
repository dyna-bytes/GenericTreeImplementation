#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

struct rb_root root;

struct class {
    int data;
    struct rb_node rb_node;
};

struct rb_node *search(int data, struct rb_node *rb_node) {
    struct class *current = NULL;
    if (!rb_node) return NULL;

    current = container_of(rb_node, struct class, rb_node);
    if (!current) return NULL;

    if (data == current->data) return rb_node;

    if (data <= current->data) {
        if (!rb_node->left) return rb_node;
        return search(data, rb_node->left);
    } else {
        if (!rb_node->right) return rb_node;
        return search(data, rb_node->right);
    }
}

int insert(int data, struct rb_root *rb_root) {
    struct rb_node *leaf_node;

    if (!rb_root->rb_node) {
        struct class *class = malloc(sizeof(struct class));
        class->data = data;
        class->rb_node.color = RED;
        class->rb_node.left = NULL;
        class->rb_node.right = NULL;
        class->rb_node.parent = NULL;

        is_root(&class->rb_node);
        return 0;
    }

    leaf_node = search(data, rb_root->rb_node);

    struct class *leaf_class =
        container_of(leaf_node, struct class, rb_node);

    if (leaf_class->data == data)
        return -1;

    struct class *class = malloc(sizeof(struct class));
    class->data = data;
    class->rb_node.color = RED;
    class->rb_node.left = NULL;
    class->rb_node.right = NULL;

    class->rb_node.parent = leaf_node;
    if (data <= leaf_class->data) {
        leaf_node->left = &class->rb_node;
        class->rb_node.parent = leaf_node;
    }
    else {
        leaf_node->right = &class->rb_node;
        class->rb_node.parent = leaf_node;
    }

    is_root(&class->rb_node);
    return 0;
}

struct rb_node *grandparent(struct rb_node *n) {
    if (n && n->parent)
        return n->parent->parent;
    return NULL;
}

struct rb_node *uncle(struct rb_node *n) {
    struct rb_node *g = grandparent(n);
    if (!g) return NULL; // No grandparent means no uncle

    if (n->parent == g->left) return g->right;
    else return g->left;
}

static void color_filp(struct rb_node *p, struct rb_node *g) {
    p->color = BLACK;
    g->color = RED;
}

/**
 * N has right child C
 *
 * AS-IS         TO-BE
 *  p             p
 *   \             \
 *   [n]           [c]
 *     \           /
 *     [c]       [n]
 *     /           \
 *    l             l
 *
 */
static void rotate_left(struct rb_node *n) {
    struct rb_node *c = n->right;
    struct rb_node *p = n->parent;

    if (c->left) c->left->parent = n;

    n->right = c->left;
    n->parent = c;
    c->left = n;
    c->parent = p;

    if (p) {
        if (p->left == n) p->left = c;
        else p->right = c;
    } else
        root.rb_node = c;
}


/**
 * N has left child C
 *
 * AS-IS         TO-BE
 *      p           p
 *     /           /
 *   [n]         [c]
 *   /             \
 * [c]             [n]
 *   \               \
 *    r               r
 */
static void rotate_right(struct rb_node *n) {
    struct rb_node *c = n->left;
    struct rb_node *p = n->parent;

    if (c->right) c->right->parent = n;

    n->right = c->right;
    n->parent = c;
    c->right = n;
    c->parent = p;

    if (p) {
        if (p->right == n) p->right = c;
        else p->left = c;
    } else
        root.rb_node = c;
}

/**
 * insert case 1
 * Check if N is root.
 */
void is_root(struct rb_node *n) {
    if (n->parent == NULL) {
        n->color = BLACK;
        root.rb_node = n;
    }
    else has_black_parent(n); // N has parent
}

/**
 * insert case 2
 * N has parent.
 * Check if N has black parent.
 */
void has_black_parent(struct rb_node *n) {
    if (n->parent->color == BLACK) return; // Tree is still valid
    else has_red_uncle_with_red_parent(n); // N has red parent
}

/**
 * insert case 3
 * N has parent and uncle. N has red parent.
 * Check if N has red uncle.
 */
void has_red_uncle_with_red_parent(struct rb_node *n) {
    struct rb_node *u = uncle(n), *g = grandparent(n);

    if (u && u->color == RED) {
        u->color = BLACK;
        color_filp(u->parent, g);
    } else // N has black uncle
        is_inside_descendant_with_red_parent_black_uncle(n);
}

/**
 * insert case 4
 * N has red parent and black uncle.
 * Check if N is inside descendant.
 */
void is_inside_descendant_with_red_parent_black_uncle(struct rb_node *n) {
    struct rb_node *g = grandparent(n);

    if ((n == n->parent->right) && (n->parent == g->left)) {
        rotate_left(n->parent);
        n = n->left; // P is now N's left child.
        // Keep search descendants under P.
    } else if ((n == n->parent->left) && (n->parent == g->right)) {
        rotate_right(n->parent);
        n = n->right; // P is now N's right child.
        // Keep search descendants under P.
    }

    is_outside_descendant_with_red_parent_black_uncle(n);
}

/**
 * insert case 5
 */
void is_outside_descendant_with_red_parent_black_uncle(struct rb_node *n) {
    struct rb_node *g = grandparent(n);

    color_filp(n->parent, g);
    if (n == n->parent->left)
        rotate_right(g);
    else
        rotate_left(g);
}

void display_postorder(struct rb_node *current, int indent) {
    if (!current) return;

    indent++;
    display_postorder(current->right, indent);

    for (int i = 0; i < indent; i++)
        printf("%4c", ' ');
    struct class* current_class = container_of(current, struct class, rb_node);
    printf("%d\n", current_class->data);

    display_postorder(current->left, indent);
}
#define DISPLAY_POSTORDER(root_node) \
    display_postorder(root_node, -1);

int main() {
    insert(1, &root);
    insert(2, &root);
    insert(3, &root);
    insert(4, &root);
    insert(5, &root);

    DISPLAY_POSTORDER(root.rb_node);
    return 0;
}