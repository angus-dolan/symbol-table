/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	Once a line has been identified as containing a variable instance.
	The line's data is passed to create_var_instance, which will extract all
	the required data and then add the variable instance to the BST.
*/
#pragma once

#include "BST.h"
#include <string>

using namespace std;

void create_var_instance(BST* root, string line, int &line_num, string &parent_func, bool from_func);