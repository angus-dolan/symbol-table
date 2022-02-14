/*
    Author: Angus Dolan
    Last Modified: 02/05/21

    Description:
    Class for creating a variable/function identifier ready to be
    placed in the BST.
*/
#pragma once

#include <string>

using namespace std;

class Identifier
{
    public:
        string name;
        int line;
        string category;
        string type;
        int count;
};