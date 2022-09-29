/////////////////////////////////////////////////////////////////////////////////////////////
// token.cpp
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
#include"token.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// The order of operations of the program. * / and % are greater than - and +
/////////////////////////////////////////////////////////////////////////////////////////////
int Token::precedence(char token) {
	if( token == '*' || token == '/' || token == '%') {
		return 2;
	} else if(  token == '-' || token == '+') {
		return 1;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Checks to see if given token is a operand
/////////////////////////////////////////////////////////////////////////////////////////////
bool Token::isOperand(char token) {
	if( token >= 'A' && token <= 'Z' || token >= '0' && token <= '9') {
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Checks to see if given token is a operator
/////////////////////////////////////////////////////////////////////////////////////////////
bool Token::isOperator(char token) {
	if( token == '-' || token == '+' || token == '*' || token == '/' || token == '%') {
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Checks to see if given token is a parentheses
/////////////////////////////////////////////////////////////////////////////////////////////
bool Token::isParentheses(char token) {
	if(  token == '(' || token == ')') {
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Creates tokens based of of the infix
/////////////////////////////////////////////////////////////////////////////////////////////
string Token::tokenize(string infix) {
	int pEqualizer = 0;
	for (int i = 0; i < infix.length(); i++) {
		if( isOperator(infix[i]) && isOperator(infix[i+1])|| isOperator(infix[0]) || isOperator(infix[infix.length() - 1])) {
			return "Invalid operator placement";
		} else if( !isOperator(infix[i]) && !isOperand(infix[i]) && !isParentheses(infix[i])) {
			return "Invalid operator or operand";
		} else if(isParentheses(infix[i])) {
			pEqualizer++;
			tokens += infix[i];
			tokens += ' ';
		} else if(isOperator(infix[i])) {
			tokens += infix[i];
			tokens += ' ';
		} else if( isOperand(infix[i]) && isOperand(infix[i+1]) ) {
			while( i < infix.length() && isOperand(infix[i])) {
				tokens += infix[i];
				i++;
			}
			i--;
			tokens += ' ';
		} else {
			tokens += infix[i];
			tokens += ' ';
		}
	}
	if( pEqualizer % 2 == 0) {
		return tokens;
	} else {
		return "Invalid number of matching parentheses";
	}
}
