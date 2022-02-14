/*
    Author: Angus Dolan
    Last Modified: 02/05/21

    Description:
    Contains the code used for the binary search tree for the symbol table.
*/
#pragma once

#include "Identifier.h"
#include <string>

using namespace std;

struct node 
{
    Identifier data;
    node* left;
    node* right;
};

class BST
{
    node* root;
    void insert(node** leaf, Identifier*); // Insert an item into the tree
    node* find(node*, string); // Find an item in the tree
    void destroy_tree(node*); // Destroy tree instance and free memory allocated to it
    void in_order(node*, ostream&); // Print the tree in order
    void BST::update(node* leaf, Identifier*); // Update the tree, if an item doesn't exist - create new. Otherwise increment the count of an existing identifier.

    public:
        BST(); // Contructor for the BST class
        ~BST(); // Destructor which destroys the BST instance and free's the memory allocated
        void insert(Identifier*); // Public helper function to call insert
        void BST::update(Identifier*); // Public helper function to call update
        node* find(string); // Public helper function call find
        void destroy_tree(); // Public helper function to insert into destroy tree
        void display(ostream&); // Public helper function to print tree
};