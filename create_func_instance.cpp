/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	Once a line has been identified as containing a function instance.
	The line's data is passed to create_func_instance, which will extract all
	the required data and then add the function instance to the BST.
*/
#include "create_func_instance.h"
#include "Identifier.h"
#include "BST.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// root = root of tree
// line = line data
// line_num = line number of instance
string create_func_instance(BST *root, string line, int &line_num)
{
	stringstream stream(line);
	string return_type;
	string func_name;
	string token;

	int i = 0;
	while (stream >> token)
	{
		if (i == 0)
		{
			// Return type
			return_type = token;
		}
		else if (i == 1)
		{
			// Function name
			func_name = token;
		} 

		i++;
	}

	// Update tree
	Identifier* result = new Identifier;
	result->name = func_name;
	result->line = line_num;
	result->category = "function";
	result->type = return_type;
	result->count = 0;
	root->update(result);
	
	// Return function name
	return func_name;
}