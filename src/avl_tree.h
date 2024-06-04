// FILE: avl_tree.h
// CLASS PROVIDED: avl_tree
//
// CONSTRUCTORS AND DECONSTRUCTORS:
//  avl_tree()
//      Initializes an empty AVL tree
//
//  ~avl_tree()
//      Deletes entire tree
//
// MUTATORS:
//  void rightRotate(node* rotation_node)
//      Initiates a single right rotation
//
//  void leftRotate(node* rotation_node)
//      Initates a single left rotation
//
//  void doubleRightRotate(node* rotation_node)
//      Initiates a double right, or right left, rotation
//
//  void doubleLeftRotate(node* rotation_node)
//      Initiates a double left, or left right, rotation
//
//  void insert_node_helper(node* insertion_node, node* previous_node, node* search_node)
//      Inserts a node in the tree recursively
//
//  void delete_key_helper(int node_key, node* previous_node, node* search_node)
//      Deletes a node from the tree that matches the key provided; recursive
//
//  void rebalance_node(node* unbalanced node)
//      Rebalances a node based on the height of its subtrees. Nodes in an AVL
//      tree should have a balance of ±1, where
//      balance = (height of left subtree) - (height of right subtree)
//
//  void update_height(node* in_node)
//      Updates the height of the node passed in. Height is determined by its children,
//      height = 1 + max(height of left subtree, height of right subtree). The max()
//      function returns the largest of the two values passed into it
//
// ACCESSORS:
//  void insert_node(node* insertion_node)
//      Inserts a node into the tree with the help of a helper function (see
//      insert_node_helper() function)
//
//  void delete_key(int node_key)
//      Deletes a node from the tree with the same key as the one passed in
//      (see delete_key_helper() function)
//
//  void print_tree()
//      Prints the entirety of the AVL tree in inorder traversal order (see
//      print_tree_helper() function)
//
//  void print_tree_helper(node* traversal node)
//      Recursively prints the tree

#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>

struct node {
    int key;
    node* left;
    node* right;
    node* parent;
    int height = 0;

    node(int key_in = 0, int height_in = 0, node* left_in = nullptr, node* right_in = nullptr) : key(key_in), left(left_in), right(right_in), height(height_in) {}
};

class avl_tree {
    public:
        // constructor & destructor
        avl_tree();
        ~avl_tree();

        // rotations
        void rightRotate(node* rotation_node);
        void leftRotate(node* rotation_node);
        void doubleRightRotate(node* rotation_node);
        void doubleLeftRotate(node* rotation_node);

        // insert & delete
        void insert_node(node* insertion_node);
        void delete_key(int node_key);

        // search
        node* successor_node(node* in_node);
        node* predecessor_node(node* in_node);

        // helper functions
        void rebalance_node(node* unbalanced_node);
        void update_height(node* in_node);
        void insert_node_helper(node* insertion_node, node* previous_node, node* search_node);
        void delete_key_helper(int node_key, node* previous_node, node* search_node);

        // print
        void print_tree();
        void print_tree_helper(node* traversal_node);
    private:
        node* root;
};

#endif