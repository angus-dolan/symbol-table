/*
	Author: Angus Dolan
	Last Modified: 02/05/21

	Description:
	classify_line contains the functions used in main() to figure out
	what each line of data from the .c file contains.
*/
#include "classify_line.h"

#include <string>
#include <sstream>
#include <tuple>

using namespace std;

// All the possible variable types
string variable_types[] = { "int", "char", "float", "double", "short", "long long", "long" };

// has_if:
// Returns true when a string has a if statment
// line = line data
bool has_if(string& line)
{
	size_t found = line.find("if");
	if (found != string::npos) {
		return true;
	} else {
		return false;
	}
}

// has_while:
// Returns true when a string has a while loop
// line = line data
bool has_while(string& line)
{
	size_t found = line.find("while");
	if (found != string::npos) {
		return true;
	}
	else {
		return false;
	}
}

// has_for:
// Returns true when a string has a for loop
// line = line data
bool has_for(string& line)
{
	size_t found = line.find("for");
	if (found != string::npos) {
		return true;
	}
	else {
		return false;
	}
}

// variable_declarations:
// Returns the number of variable declarations in a string
// line = line data
int variable_declarations(string &line)
{
	stringstream stream(line);
	string prev_token;
	string token;

	int count = 0;

	while (stream >> token)
	{
		// Check for long long
		if (token.compare(prev_token) == 0)
			continue;

		// Remove pointer from token
		size_t found = token.find("*");
		if (found != string::npos)
			token.erase(found, 1);

		// Look for token and type match
		for (const string& type : variable_types)
		{
			if (token.compare(type) == 0)
				count++;
		}

		prev_token = token;
	}

	// Return count
	return count;
}

// variables_within_brackets:
// Like variable_declarations, returns number of variable declarations in a string
// only within brackets.
// line = line data
int variables_within_brackets(string &line)
{
	stringstream stream(line);
	string prev_token;
	string token;

	int count = 0;
	int flag = 0;

	while (stream >> token)
	{

		if (token.compare("(") == 0 || token.compare(")") == 0)
			flag++;

		// When within "(" and ")"
		if (flag == 1)
		{
			// Check for long long
			if (token.compare(prev_token) == 0)
				continue;

			// Remove pointer from token
			size_t found = token.find("*");
			if (found != string::npos)
				token.erase(found, 1);

			// Look for token and type match
			for (const string& type : variable_types)
			{
				if (token.compare(type) == 0)
					count++;
			}

			prev_token = token;
		}
		else if (flag == 2)
		{
			break;
		}
	}

	// Return count
	return count;
} 

// multiple_variable_references: 
// Used to check for multiple var references in a single line
// returns a tuple(string, int) with string being the var name, int being number of 
// times that var name was referenced on the same line it was declared.
// line = line data
tuple<string, int> multiple_variable_references(string line)
{
	stringstream stream(line);
	string target_var;
	string token;

	bool flag = false;
	int count = 0;
	int i = 0;

	while (stream >> token)
	{
		if (token.compare("int") == 0)
		{
			flag = true;
		}
		if (flag)
		{
			if (i == 1)
				target_var = token;
			if (token.compare(target_var) == 0) count++;

			i++;
		}
	}

	// Return count
	return make_tuple(target_var, count);
}

// function_instance:
// Returns true if string contains a function declaration
// line = line data
bool function_instance(string &line)
{
	size_t equal_operator = line.find("="); // if equal operator present, can't be a func declaration

	if (!has_if(line) && !has_for(line) && !has_while(line) && variable_declarations(line) > 0 && equal_operator == string::npos) {
		size_t found = line.find("(");
		if (found != string::npos)
			return true;
	}

	return false;
}

bool is_main(string& line)
{
	size_t found = line.find("main");
	if (found != string::npos) {
		return true;
	}
	else {
		return false;
	}
}

// is_whitespace: 
// Returns t/f depending if a string is whitepace.
// Code adapted from: https://stackoverflow.com/questions/6325483/c-check-if-string-is-space-or-null
// s = string data
bool is_whitespace(string &s) 
{
	for (int index = 0; index < s.length(); index++) {
		if (!std::isspace(s[index]))
			return false;
	}
	return true;
}
