/*
    Author: Angus Dolan
    Last Modified: 02/05/21

    Description:
    Contains the code used for the binary search tree for the symbol table.
*/
#include "BST.h"
#include "Identifier.h"

#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

// Contructor for the BST class
BST::BST()
{
    root = NULL;
}

// Destructor which destroys the BST instance and free's the memory allocated
BST::~BST()
{
    destroy_tree();
}

// Public helper function to call insert
// data = identifier instance containing data to be added to tree
void BST::insert(Identifier *data)
{
    if (root != NULL) {
        insert(&root, data);
    }
    else {
        root = new node;
        root->data = *data;
        root->left = NULL;
        root->right = NULL;
    }
}

// Insert an item into the tree
// leaf = root of tree
// data = identifier instance containing data to be added to tree
void BST::insert(node** leaf, Identifier* data)
{
    if (*leaf == nullptr) {
        *leaf = new node;
        (*leaf)->data = *data;
        (*leaf)->left = nullptr;
        (*leaf)->right = nullptr;
    }
    else if (data->name < (*leaf)->data.name) {
        insert(&((*leaf)->left), data);
    }
    else {
        insert(&((*leaf)->right), data);
    }
}

// Public helper function call find
// target = name of function/variable to find
node* BST::find(string target)
{
    return find(root, target); // start from the root
}

// Find an item in the tree
// leaf = root of tree
// target = name of function/variable to find
node* BST::find(node* leaf, string target)
{
    if (leaf == NULL) {
        return NULL;
    }
    else if (target == leaf->data.name) {
        return leaf;
    }
    else if (target < leaf->data.name) {
        return find(leaf->left, target);
    }
    else return find(leaf->right, target);
}

// Public helper function to call update
// target = function/variable to update
void BST::update(Identifier* target)
{
    update(root, target); // start from the root
}

// Update the tree, if an item doesn't exist - create new. 
// Otherwise increment the count of an existing identifier
// leaf = root of tree
// target = function/variable to update
void BST::update(node* leaf, Identifier* target)
{
    if (leaf == NULL) {
        // Insert new
        insert(target);
    }
    else if (target->name == leaf->data.name) {
        // Update existing
        leaf->data.count++;
    }
    else if (target->name < leaf->data.name) {
        update(leaf->left, target);
    }
    else update(leaf->right, target);
}

// Print the tree in order
// t = root of tree
// output = output file stream
void BST::in_order(node* t, ostream &output)
{
    if (t != NULL) {
        in_order(t->left, output);
        output << t->data.name << ", line " << t->data.line << ", " << t->data.category << ", " << t->data.type << ", referenced " << t->data.count << endl;
        in_order(t->right, output);
    }
}

// Public helper function to print tree
// output = output file stream
void BST::display(ostream &output)
{
    in_order(root, output);
}

// Public helper function to insert into destroy tree
void BST::destroy_tree()
{
    destroy_tree(root);
}

// Destroy tree instance and free memory allocated to it
// leaf = root of tree to start deleting from
void BST::destroy_tree(node* leaf)
{
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
    }

    delete leaf;
}