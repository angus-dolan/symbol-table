/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description: 
	Symbol Table application made for Coursework 2 of Programming Fundamentals. 
	Please see readme for details such as building and using the application.
*/
#include "classify_line.h"
#include "create_func_instance.h"
#include "create_var_instance.h"
#include "BST.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>

using namespace std;

// Print data to console
void print_console(int num_vars, int num_func, int num_if, int num_for, int num_while) {
	cout << "Variables: " << num_vars << endl;
	cout << "Functions: " << num_func << endl;
	cout << "If statements: " << num_if << endl;
	cout << "For loops: " << num_for << endl;
	cout << "While loops: " << num_while << endl;
}

int main(int argc, char** argv)
{
	// Get input file from CL args
	string input_f;
	for (int i = 0; i < argc; ++i)
		if (i == 1) input_f = argv[i];
	ifstream input("./src/" + input_f);

	// Output file
	std::ofstream output("out/identifiers.txt");

	// Define tree root
	BST* root = new BST();

	// Init console output variables
	int num_vars = 0;
	int num_func = 0;
	int num_if = 0;
	int num_for = 0;
	int num_while = 0;

	bool func_flag = false;
	string parent_func;

	int line_num = 1;
	string prev_line;
	string line;

	while (getline(input, line))
	{
		bool func_instance = function_instance(line);
		int var_declarations = variable_declarations(line);

		// Line token
		stringstream stream(line);
		string token;

		// BST References
		while (stream >> token)
		{
			Identifier* blank = new Identifier;

			// Catch functions outside main
			if (parent_func.length() > 0 && parent_func.compare("main") != 0)
			{
				node* test = root->find(token);
				if (test && (test->data.category.compare("function") == 0))
				{
					blank->name = token;
					root->update(blank);
				}
			}
			// Variables with parent function, outside of main
			if (parent_func.length() > 0 && parent_func.compare("main") != 0)
			{
				node* test = root->find(token + " (" + parent_func + ")");
				if (test)
				{
					blank->name = token + " (" + parent_func + ")";
					root->update(blank);
				}
			}
			else
			{
				node* test = root->find(token);
				if (test)
				{
					blank->name = token;
					root->update(blank);
				}
			}
		}

		// FUNCTION
		if (func_instance)
		{
			num_func++;
			parent_func = create_func_instance(root, line, line_num); // create function instance

			// Open parent function flag
			// When function is NOT main
			if (!is_main(line)) func_flag = true;

			// VARIABLE in FUNCTION
			if (var_declarations > 0) {
				size_t found = line.find("void");

				// Create variable instance
				if (!is_main(line))
				{
					create_var_instance(root, line, line_num, parent_func, true); // create variable instance
				}

				// Update num_vars (console output)
				if (found != string::npos)
				{
					num_vars += var_declarations; // function returns type
				}
				else
				{
					num_vars += var_declarations - 1; // function returns void
				}
			}

		}

		// VARIABLE
		if (var_declarations > 0 && !func_instance) {
			// Line contains variable instance
			if (has_for(line) || has_while(line))
				create_var_instance(root, line, line_num, parent_func, true); // create variable instance
			else
				create_var_instance(root, line, line_num, parent_func, false); // create variable instance

			num_vars += var_declarations;
		}
		// IF
		if (has_if(line))
			num_if++;
		// FOR
		if (has_for(line))
			num_for++;
		// WHILE
		if (has_while(line))
			num_while++;

		// Close parent function flag
		if (func_flag && is_whitespace(line))
		{
			func_flag = false;
			parent_func = "";
		}

		// Check for multiple var references in a single line
		if (variable_declarations(line) > 0) {
			string name;
			int num;

			tie(name, num) = multiple_variable_references(line); // recieve name, num as a tuple

			if (num > 1) {
				Identifier* blank = new Identifier;
				blank->name = name;

				for (int k = 1; k < num; k++) {
					root->update(blank);
				}
			}
		}
		
		prev_line = line;
		line_num++;
	}

	// Print to console
	print_console(num_vars, num_func, num_if, num_for, num_while);

	// Print to file and free memory
	root->display(output);
	root->destroy_tree();

	// Close IO
	input.close();
	output.close();

	return 0;
} 