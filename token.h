/////////////////////////////////////////////////////////////////////////////////////////////
// token.h
// Used to convert to tokens
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
#include <string>
#include <stack>

#ifndef TOKEN_H 
#define TOKEN_H

class Token {
	public:
		// Order of operations
		int precedence(char);
		// Legal operands
		bool isOperand(char);
		// Legal operators
		bool isOperator(char);
		// Check if parentheses
		bool isParentheses(char);
		// Splits infix to make tokens
		std::string tokenize(std::string);
	private:
		std::string tokens;
};
#endif 