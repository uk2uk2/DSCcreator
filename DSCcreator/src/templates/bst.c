const char* BST_TEMPLATE_C = R"(
#include "bst.h"

static BSTNode* create_node(void* data) {
    BSTNode* node = malloc(sizeof(BSTNode));
    if (node) {
        node->data = data;
        node->left = node->right = NULL;
        node->height = 1;
    }
    return node;
}

static int get_height(BSTNode* node) {
    return node ? node->height : 0;
}

static int get_balance(BSTNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

static void update_height(BSTNode* node) {
    if (!node) return;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    node->height = 1 + (left_height > right_height ? left_height : right_height);
}

static BSTNode* rotate_right(BSTNode* y) {
    BSTNode* x = y->left;
    BSTNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

static BSTNode* rotate_left(BSTNode* x) {
    BSTNode* y = x->right;
    BSTNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

static BSTNode* balance_node(BSTNode* node) {
    if (!node) return NULL;

    update_height(node);
    int balance = get_balance(node);

    // Left Heavy
    if (balance > 1) {
        if (get_balance(node->left) < 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }

    // Right Heavy
    if (balance < -1) {
        if (get_balance(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }

    return node;
}

static BSTNode* insert_recursive(BSTNode* node, void* data, 
                               int (*compare)(const void*, const void*)) {
    if (!node) return create_node(data);

    int cmp = compare(data, node->data);
    if (cmp < 0)
        node->left = insert_recursive(node->left, data, compare);
    else if (cmp > 0)
        node->right = insert_recursive(node->right, data, compare);
    else
        return node;  // Duplicate data

    return balance_node(node);
}

// ... more implementation
)";const char* BST_TEMPLATE_C = R"(
#include "bst.h"

static BSTNode* create_node(void* data) {
    BSTNode* node = malloc(sizeof(BSTNode));
    if (node) {
        node->data = data;
        node->left = node->right = NULL;
        node->height = 1;
    }
    return node;
}

static int get_height(BSTNode* node) {
    return node ? node->height : 0;
}

static int get_balance(BSTNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

static void update_height(BSTNode* node) {
    if (!node) return;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    node->height = 1 + (left_height > right_height ? left_height : right_height);
}

static BSTNode* rotate_right(BSTNode* y) {
    BSTNode* x = y->left;
    BSTNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

static BSTNode* rotate_left(BSTNode* x) {
    BSTNode* y = x->right;
    BSTNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

static BSTNode* balance_node(BSTNode* node) {
    if (!node) return NULL;

    update_height(node);
    int balance = get_balance(node);

    // Left Heavy
    if (balance > 1) {
        if (get_balance(node->left) < 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }

    // Right Heavy
    if (balance < -1) {
        if (get_balance(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }

    return node;
}

static BSTNode* insert_recursive(BSTNode* node, void* data, 
                               int (*compare)(const void*, const void*)) {
    if (!node) return create_node(data);

    int cmp = compare(data, node->data);
    if (cmp < 0)
        node->left = insert_recursive(node->left, data, compare);
    else if (cmp > 0)
        node->right = insert_recursive(node->right, data, compare);
    else
        return node;  // Duplicate data

    return balance_node(node);
}

// ... more implementation
)";
