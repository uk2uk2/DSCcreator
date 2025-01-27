const char* RBTREE_TEMPLATE_C = R"(
#include "rbtree.h"

static RBNode* create_node(void* key, void* value) {
    RBNode* node = malloc(sizeof(RBNode));
    if (!node) return NULL;
    
    node->key = key;
    node->value = value;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    
    return node;
}

RBTree* rbtree_create(int (*compare)(const void*, const void*),
                     void (*destroy_key)(void*),
                     void (*destroy_value)(void*)) {
    RBTree* tree = malloc(sizeof(RBTree));
    if (!tree) return NULL;
    
    tree->root = NULL;
    tree->size = 0;
    tree->compare = compare;
    tree->destroy_key = destroy_key;
    tree->destroy_value = destroy_value;
    
    return tree;
}

static void destroy_node(RBTree* tree, RBNode* node) {
    if (!node) return;
    
    destroy_node(tree, node->left);
    destroy_node(tree, node->right);
    
    if (tree->destroy_key) tree->destroy_key(node->key);
    if (tree->destroy_value) tree->destroy_value(node->value);
    free(node);
}

void rbtree_destroy(RBTree* tree) {
    if (!tree) return;
    destroy_node(tree, tree->root);
    free(tree);
}

static void rotate_left(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    
    if (y->left) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (!x->parent) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

static void rotate_right(RBTree* tree, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    
    if (x->right) {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    
    if (!y->parent) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    
    x->right = y;
    y->parent = x;
}

static void fix_insert(RBTree* tree, RBNode* node) {
    RBNode* parent = NULL;
    RBNode* grandparent = NULL;
    
    while (node != tree->root && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        
        if (parent == grandparent->left) {
            RBNode* uncle = grandparent->right;
            
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotate_left(tree, node);
                    parent = node->parent;
                }
                
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_right(tree, grandparent);
            }
        } else {
            RBNode* uncle = grandparent->left;
            
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotate_right(tree, node);
                    parent = node->parent;
                }
                
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_left(tree, grandparent);
            }
        }
    }
    
    tree->root->color = BLACK;
}

int rbtree_insert(RBTree* tree, void* key, void* value) {
    if (!tree) return DS_ERROR;
    
    RBNode* node = create_node(key, value);
    if (!node) return DS_ERROR;
    
    RBNode* y = NULL;
    RBNode* x = tree->root;
    
    while (x) {
        y = x;
        int cmp = tree->compare(key, x->key);
        if (cmp < 0) {
            x = x->left;
        } else if (cmp > 0) {
            x = x->right;
        } else {
            // Key exists, update value
            if (tree->destroy_value) {
                tree->destroy_value(x->value);
            }
            x->value = value;
            free(node);
            return DS_OK;
        }
    }
    
    node->parent = y;
    
    if (!y) {
        tree->root = node;
    } else if (tree->compare(key, y->key) < 0) {
        y->left = node;
    } else {
        y->right = node;
    }
    
    fix_insert(tree, node);
    tree->size++;
    
    return DS_OK;
}

// ... more implementation including delete, search, and verification
)";
