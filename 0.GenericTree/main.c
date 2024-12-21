#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct __node {
    struct __node *left;
    struct __node *right;
} node;

typedef struct __class {
    int data;
    node tree_node;
} class;

node *root;

typedef enum {LEFT, RIGHT} FLAG;

void insert_data(int data, node *parent, FLAG flag) {
    class *current = malloc(sizeof(class));
    current->data = data;

    node *node = &current->tree_node;
    node->left = NULL;
    node->right = NULL;

    if (!root) {
        root = node;
        return;
    }

    if (flag == LEFT) parent->left = node;
    else parent->right = node;
}

/**
 * display_postorder
 * Display tree in post order manner.
 * It shows tree rotated to the left.
 */
void display_postorder(node *current, int indent) {
    if (!current) return;

    indent++;
    display_postorder(current->right, indent);

    for (int i = 0; i < indent; i++)
        printf("%4c", ' ');
    class* current_class = container_of(current, class, tree_node);
    printf("%d\n", current_class->data);

    display_postorder(current->left, indent);
}
#define DISPLAY_POSTORDER(root_node) \
    display_postorder(root_node, -1);



void arrange_inorder(node *current, int (*array)[10], int* row, int* col) {
    if (!current) return;

    (*row)++;
    arrange_inorder(current->left, array, row, col);

    class* current_class = container_of(current, class, tree_node);
    array[(*row)][(*col)] = current_class->data;

    (*col)++;
    arrange_inorder(current->right, array, row, col);

    (*row)--;
}

void display_inorder(node *root) {
    int row = -1;
    int col = 0;
    int array[10][10] = {0, };

    arrange_inorder(root, array, &row, &col);

    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (array[r][c]) printf("%4d", array[r][c]);
            else printf("%4c", ' ');
        }
        printf("\n");
    }
}

int main() {
    insert_data(1, root, LEFT);
    insert_data(2, root, LEFT);
    insert_data(3, root, RIGHT);
    insert_data(4, root->left, LEFT);
    insert_data(5, root->left, RIGHT);
    insert_data(6, root->right, LEFT);
    insert_data(7, root->right, RIGHT);

    // DISPLAY_POSTORDER(root);
    display_inorder(root);
    return 0;
}