// FILE: avl_tree.cpp
// CLASS IMPLEMENTED: avl_tree

#include "avl_tree.h"

avl_tree::avl_tree() {root = nullptr;}

void avl_tree::rightRotate(node* rotation_node) {
    //     a <- rotation_node
    //    /  
    //   b <- left_child
    //  / \
    // c   d

    node* left_child = rotation_node->left;

    // check if rotation node is root node
    if (rotation_node == root) {
        root = left_child;
    }
    else {
        if (rotation_node->parent->left == rotation_node) {
            rotation_node->parent->left = left_child;
        }
        else {
            rotation_node->parent->right = left_child;
        }
    }
    left_child->parent = rotation_node->parent;

    // link node a with node d, and vice versa
    rotation_node->left = left_child->right;
    if (left_child->right != nullptr) {
        left_child->right->parent = rotation_node;
    }

    // link node a with node b, and vice versa
    rotation_node->parent = left_child;
    left_child->right = rotation_node;

    // update height of rotated nodes
    update_height(rotation_node);
    update_height(left_child);
}
void avl_tree::leftRotate(node* rotation_node) {
    //  a <- rotation_node
    //   \
    //    b <- right_child
    //   / \
    // d    c

    node* right_child = rotation_node->right;

    // check if rotation node is root node
    if (rotation_node == root) {
        root = right_child;
    }
    else {
        if (rotation_node->parent->right == rotation_node) {
            rotation_node->parent->right = right_child;
        }
        else {
            rotation_node->parent->left = right_child;
        }
    }
    right_child->parent = rotation_node->parent;

    // link node a with node d, and vice versa
    rotation_node->right = right_child->left;
    if (right_child->left != nullptr) {
        right_child->left->parent = rotation_node;
    }

    // link node a with node b, and vice versa
    rotation_node->parent = right_child;
    right_child->left = rotation_node;

    // update height of rotated nodes
    update_height(rotation_node);
    update_height(right_child);
}

// left-right
void avl_tree::doubleRightRotate(node* rotation_node) {
    // left rotate on left subtree
    leftRotate(rotation_node->left);

    // right rotate on rotation node
    rightRotate(rotation_node);
}

// right-left
void avl_tree::doubleLeftRotate(node* rotation_node) {
    // right rotate on right subtree
    rightRotate(rotation_node->right);

    // left rotate on rotation node
    leftRotate(rotation_node);
}

void avl_tree::rebalance_node(node* unbalanced_node) {
    // check balance of search node
    // if neg, node is right heavy
    // if pos, node is left heavy
    int balance = ((unbalanced_node->left == nullptr) ? 0 : unbalanced_node->left->height) - ((unbalanced_node->right == nullptr) ? 0 : unbalanced_node->right->height);
    if (balance < -1) {
        if (unbalanced_node->right != nullptr) {

            // check if a double left rotation (right-left) is needed
            int right_balance = ((unbalanced_node->right->left == nullptr) ? 0 : unbalanced_node->right->left->height) - ((unbalanced_node->right->right == nullptr) ? 0 : unbalanced_node->right->right->height);
            if (right_balance > 0) {
                doubleLeftRotate(unbalanced_node);
            }
            else {
                leftRotate(unbalanced_node);
            }
        }
        else {
            leftRotate(unbalanced_node);
        }
    }
    else if (balance > 1) {
        if (unbalanced_node->left != nullptr) {

            // check if a double right rotation (left-right) is needed
            int left_balance = ((unbalanced_node->left->left == nullptr) ? 0 : unbalanced_node->left->left->height) - ((unbalanced_node->left->right == nullptr) ? 0 : unbalanced_node->left->right->height);
            if (left_balance < 0) {
                doubleRightRotate(unbalanced_node);
            }
            else {
                rightRotate(unbalanced_node);
            }
        }
        else {
            rightRotate(unbalanced_node);
        }
    }
    else {
        return;
    }
}

void avl_tree::insert_node(node* insertion_node) {
    // check if tree is empty
    if (root == nullptr) {
        root = insertion_node;
        root->height = 1;
    }
    else {
        insert_node_helper(insertion_node, root, root);
    }
}

void avl_tree::insert_node_helper(node* insertion_node, node* previous_node, node* search_node) {
    // recursive condition:
    // traverses through the tree until a valid null node is found to insert
    //  the new node
    if (search_node != nullptr) {
        (insertion_node->key < search_node->key) ? insert_node_helper(insertion_node, search_node, search_node->left) : insert_node_helper(insertion_node, search_node, search_node->right);
    }
    else {
        search_node = insertion_node;
        
        // link new node with previous node
        search_node->parent = previous_node;
        if (search_node->key < previous_node->key) {
            previous_node->left = search_node;
        }
        else {
            previous_node->right = search_node;
        }
    }

    // update height of nodes
    update_height(search_node);

    rebalance_node(search_node);
}

void avl_tree::delete_key(int node_key) {
    delete_key_helper(node_key, root, root);
}

void avl_tree::delete_key_helper(int node_key, node* previous_node, node* search_node) {
    // recursive condition:
    // traverses through the tree until the desired node is found
    if (search_node->key != node_key) {
        (node_key < search_node->key) ? delete_key_helper(node_key, search_node, search_node->left) : delete_key_helper(node_key, search_node, search_node->right);
    }
    else {
        // check deletion conditions:
        //  1: leaf node
        //  2: one child
        //  3: two children
        if (search_node->left == nullptr && search_node->right == nullptr) {
            (previous_node->left == search_node) ? previous_node->left = nullptr : previous_node->right = nullptr;
            
            delete search_node;

            search_node = previous_node;
        }
        else if ((search_node->left != nullptr && search_node->right == nullptr) || (search_node->left == nullptr && search_node->right != nullptr)) {
            // node that replaces the deleted node
            node* replacing_node = (search_node->left != nullptr) ? search_node->left : search_node->right;

            // set links
            replacing_node->parent = previous_node;
            if (previous_node->left == search_node) {
                previous_node->left = replacing_node;
            }
            else {
                previous_node->right = replacing_node;
            }

            // delete node
            delete search_node;
            search_node = replacing_node;
        }
        else {
            int successor_key = successor_node(search_node)->key;
            delete_key(successor_key);
            search_node->key = successor_key;
        }
    }

    update_height(search_node);

    rebalance_node(search_node);
}

node* avl_tree::successor_node(node* in_node) {
    // successor conditions:
    //  1: right subtree is not NULL
    //  2: right subtree is NULL
    if (in_node->right != nullptr) {
        node* search_node = in_node->right;
        while (search_node->left != nullptr) {
            search_node = search_node->left;
        }
        return search_node;
    }
    else {
        node* search_node = in_node;
        node* parent = in_node->parent;

        while (parent != nullptr) {
            if (parent->left == search_node) {
                return parent;
            }
            else {
                search_node = parent;
                parent = parent->parent;
            }
        }
    }

    return nullptr;
}

node* avl_tree::predecessor_node(node* in_node) {
    // predecessor conditions:
    //  1: left subtree is not NULL
    //  2: left subtree is NULL
    if (in_node->left != nullptr) {
        node* search_node = in_node->left;
        while (search_node->right != nullptr) {
            search_node = search_node->right;
        }

        return search_node;
    }
    else {
        node* search_node = in_node;
        node* parent = in_node->parent;

        while (parent != nullptr) {
            if (parent->right == search_node) {
                return parent;
            }
            else {
                search_node = parent;
                parent = parent->parent;
            }
        }
    }

    return nullptr;
}

void avl_tree::update_height(node* in_node) {
    int left_height = (in_node->left == nullptr) ? 0 : in_node->left->height;
    int right_height = (in_node->right == nullptr) ? 0 : in_node->right->height;

    in_node->height = 1 + std::max(left_height, right_height);
}

void avl_tree::print_tree() {
    print_tree_helper(root);
    std::cout << std::endl;
}

void avl_tree::print_tree_helper(node* traversal_node) {
    if (traversal_node == nullptr) {
        return;
    }

    print_tree_helper(traversal_node->left);

    std::cout << traversal_node->key << " ";

    print_tree_helper(traversal_node->right);
}