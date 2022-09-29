/////////////////////////////////////////////////////////////////////////////////////////////
// postfix.h
// Used to convert from infix to postfix form and solve from postfix
//	- Part one – build a program that:
//	o Prompts the user for a  string of user input.
//	o Treat that string as a mathematical expression in an infix form.
//	o Convert the string into a series of tokens where each token is an operator, or a value 
//	delimited by whitespace , operator, or \n
//	- Part two – 
//	o Convert to postfix and print out the results. ( or print out an error if badly formed) 
//	- Part Three – further. 
//	o Do the math to evaluate the expression when all operands are values ( not variables)
/////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

#include"token.h"

#ifndef POSTFIX_H 
#define POSTFIX_H

class Postfix {
	public:
		// Converts infix to postfix
		std::string toPostfix(std::string);
		// Operation to use
		int operationType(char, int, int);
		// Solves postfix
		int solve(std::string);
	private:
		std::string postfix;
		std::stack<char> operators;
		std::stack<int> solution;
		Token token;
};
#endif 