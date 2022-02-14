/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	Once a line has been identified as containing a function instance.
	The line's data is passed to create_func_instance, which will extract all
	the required data and then add the function instance to the BST.
*/
#pragma once

#include "BST.h"
#include <string>

using namespace std;

string create_func_instance(BST *root, string line, int &line_num);