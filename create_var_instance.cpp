/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	Once a line has been identified as containing a variable instance.
	The line's data is passed to create_var_instance, which will extract all
	the required data and then add the variable instance to the BST.
*/
#include "create_var_instance.h"
#include "Identifier.h"
#include "BST.h"
#include "classify_line.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Data is passed to result to be added to the BST
// root = root of tree
// var_name = variable name
// line_num = line number of instance
// var_type = variable type (int, bool, etc.)
void result(BST* root, string var_name, int line_num, string var_type)
{
	Identifier* result = new Identifier;

	result->name = var_name;
	result->line = line_num;
	result->category = "variable";
	result->type = var_type;
	result->count = 0;

	root->update(result);
}

// Variables will have different names depending on the scope of the variable
// name = name of variable
// parent_func = parent function variable is contained in, i.e. it's scope
string parse_name(string &name, string &parent_func)
{
	if (parent_func.compare("main") == 0)
	{
		// Return only name for main
		return name;
	}
	else if (parent_func.length() > 0)
	{
		// Variable has parent function
		return name + " (" + parent_func + ")";
	}
	else
	{
		// Variable is standalone
		return name;
	}
}

// Main function which recieves the line and extracts the varible instance data
// root = root of tree
// line = line data
// line_num = line number of instance
// parent_func = parent function variable is contained in, i.e. it's scope
// from_func = if a var comes from a function it needs to be traversed differently to remain accurate
void create_var_instance(BST* root, string line, int &line_num, string &parent_func, bool from_func)
{
	stringstream stream(line);
	string var_type;
	string var_name;
	string token;

	if (!from_func)
	{
		int i = 0;

		// Variable is standalone
		while (stream >> token)
		{
			if (i == 1 && token.compare(var_type) == 0 )
			{
				// Long long type
				var_type = "long long";
				continue;
			}
			else if (i == 0)
			{
				// Variable type
				var_type = token;
			}
			else if (i == 1)
			{
				// Variable name 
				var_name = parse_name(token, parent_func);
			}
			else if (i == 2 && token.compare(";") == 0)
			{
				// Array Type (semicolon)
				continue;
			}
			else if (i == 2 && token.compare("=") != 0)
			{
				// Array type
				var_type = var_type + " " + token;
			}

			i++;
		}

		result(root, var_name, line_num, var_type);
	}
	else 
	{	
		int num_vars = variables_within_brackets(line);
		bool flag = false;
		int i = 0;
		 
		while (stream >> token)
		{
			if (token.compare("(") == 0)
			{
				// Start reading data
				flag = true;
				continue;
			}
			else if ((token.compare(")") == 0) || (token.compare("=") == 0 && num_vars == 1))
			{
				// Stop reading data
				flag = false;
				break;
			}
			else if (token.compare(",") == 0)
			{
				// Skip
				i = 0;
				continue;
			}

			if (flag) {
				if (i == 0)
				{
					// Variable return type
					var_type = token;
				}
				else if (i == 1)
				{
					// Variable name
					var_name = parse_name(token, parent_func);
					result(root, var_name, line_num, var_type);
				}

				i++;
			}
		}
	}
}