/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	classify_line contains the functions used in main() to figure out 
	what each line of data from the .c file contains.
*/
#pragma once
#include <string>

using namespace std;

// has_if:
// Returns true when a string has a if statment
bool has_if(string&);

// has_while:
// Returns true when a string has a while loop
bool has_while(string&);

// has_for:
// Returns true when a string has a for loop
bool has_for(string&);

// variable_declarations:
// Returns number of variable declarations in a string
int variable_declarations(string&);

// variables_within_brackets:
// Like variable_declarations, returns number of variable declarations in a string
// only within brackets.
int variables_within_brackets(string&);

// multiple_variable_references: 
// Used to check for multiple var references in a single line
// returns a tuple(string, int) with string being the var name, int being number of 
// times that var name was referenced on the same line it was declared.
tuple<string, int> multiple_variable_references(string);

// function_instance:
// Returns t/f depending if a string declares a new function
bool function_instance(string&);

// is_main: 
// Returns t/f depending if a string contains "main"
bool is_main(string&);

// is_whitespace: 
// Returns t/f depending if a string is whitepace.
// Code adapted from: https://stackoverflow.com/questions/6325483/c-check-if-string-is-space-or-null
bool is_whitespace(string&);
