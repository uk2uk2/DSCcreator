const char* BTREE_TEMPLATE_C = R"(
#include "btree.h"

static BTreeNode* btree_create_node(int t, bool leaf) {
    BTreeNode* node = malloc(sizeof(BTreeNode));
    if (!node) return NULL;

    node->keys = malloc((2 * t - 1) * sizeof(void*));
    node->values = malloc((2 * t - 1) * sizeof(void*));
    node->children = malloc(2 * t * sizeof(BTreeNode*));
    
    if (!node->keys || !node->values || !node->children) {
        free(node->keys);
        free(node->values);
        free(node->children);
        free(node);
        return NULL;
    }

    node->n = 0;
    node->leaf = leaf;
    return node;
}

BTree* btree_create(int t,
                   int (*compare)(const void*, const void*),
                   void (*destroy_key)(void*),
                   void (*destroy_value)(void*)) {
    if (t < BTREE_MIN_DEGREE) return NULL;

    BTree* tree = malloc(sizeof(BTree));
    if (!tree) return NULL;

    tree->root = NULL;
    tree->t = t;
    tree->size = 0;
    tree->compare = compare;
    tree->destroy_key = destroy_key;
    tree->destroy_value = destroy_value;

    return tree;
}

static void btree_destroy_node(BTree* tree, BTreeNode* node) {
    if (!node) return;

    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) {
            btree_destroy_node(tree, node->children[i]);
        }
    }

    for (int i = 0; i < node->n; i++) {
        if (tree->destroy_key) tree->destroy_key(node->keys[i]);
        if (tree->destroy_value) tree->destroy_value(node->values[i]);
    }

    free(node->keys);
    free(node->values);
    free(node->children);
    free(node);
}

void btree_destroy(BTree* tree) {
    if (!tree) return;
    btree_destroy_node(tree, tree->root);
    free(tree);
}

static void btree_split_child(BTree* tree, BTreeNode* x, int i) {
    BTreeNode* y = x->children[i];
    BTreeNode* z = btree_create_node(tree->t, y->leaf);
    
    // Copy the second half of y's keys and values to z
    for (int j = 0; j < tree->t - 1; j++) {
        z->keys[j] = y->keys[j + tree->t];
        z->values[j] = y->values[j + tree->t];
    }
    
    // If not leaf, copy the corresponding children
    if (!y->leaf) {
        for (int j = 0; j < tree->t; j++) {
            z->children[j] = y->children[j + tree->t];
        }
    }
    
    z->n = tree->t - 1;
    y->n = tree->t - 1;
    
    // Move keys and children in x to make room
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }
    x->children[i + 1] = z;
    
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
        x->values[j + 1] = x->values[j];
    }
    
    x->keys[i] = y->keys[tree->t - 1];
    x->values[i] = y->values[tree->t - 1];
    x->n++;
}

static void btree_insert_nonfull(BTree* tree, BTreeNode* node, void* key, void* value) {
    int i = node->n - 1;
    
    if (node->leaf) {
        while (i >= 0 && tree->compare(key, node->keys[i]) < 0) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            i--;
        }
        
        node->keys[i + 1] = key;
        node->values[i + 1] = value;
        node->n++;
    } else {
        while (i >= 0 && tree->compare(key, node->keys[i]) < 0) {
            i--;
        }
        i++;
        
        if (node->children[i]->n == 2 * tree->t - 1) {
            btree_split_child(tree, node, i);
            if (tree->compare(key, node->keys[i]) > 0) {
                i++;
            }
        }
        btree_insert_nonfull(tree, node->children[i], key, value);
    }
}

int btree_insert(BTree* tree, void* key, void* value) {
    if (!tree) return DS_ERROR;
    
    if (!tree->root) {
        tree->root = btree_create_node(tree->t, true);
        if (!tree->root) return DS_ERROR;
        
        tree->root->keys[0] = key;
        tree->root->values[0] = value;
        tree->root->n = 1;
    } else {
        if (tree->root->n == 2 * tree->t - 1) {
            BTreeNode* new_root = btree_create_node(tree->t, false);
            if (!new_root) return DS_ERROR;
            
            new_root->children[0] = tree->root;
            tree->root = new_root;
            btree_split_child(tree, new_root, 0);
            btree_insert_nonfull(tree, new_root, key, value);
        } else {
            btree_insert_nonfull(tree, tree->root, key, value);
        }
    }
    
    tree->size++;
    return DS_OK;
}

// ... more implementation
)";
