/////////////////////////////////////////////////////////////////////////////////////////////
// postfix.cpp
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
#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
#include"postfix.h"
#include"token.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// Converts tokenized infix into postfix format
/////////////////////////////////////////////////////////////////////////////////////////////
string Postfix::toPostfix(string infix) {
	if( infix[0] == 'I') {
		return "Error! Badly formed";
	}
	for( int i = 0; i < infix.length(); i++) {
		if( token.isOperand(infix[i]) && token.isOperand(infix[i+1]) ) {
			while( i < infix.length() && token.isOperand(infix[i])) {
				postfix += infix[i];
				i++;
			}
			i--;
			postfix += ' ';
		} else if( infix[i] == '(') {
			operators.push('(');
		} else if( infix[i] == ')') {
			while( operators.top() != '(') {
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
		} else if(token.isOperand(infix[i])) {
			postfix += infix[i];
			postfix += ' ';
		} else if( token.isOperator(infix[i])) {
			while(!operators.empty() && token.precedence(infix[i]) <= token.precedence(operators.top())) {
				postfix += operators.top();
				operators.pop();
			}
			operators.push(infix[i]);
		}
	}
	while( !operators.empty()) {
		postfix += operators.top();
		operators.pop();
	}
	return postfix;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Determines which operation to use
/////////////////////////////////////////////////////////////////////////////////////////////
int Postfix::operationType(char operation, int a, int b) {
	if(operation == '+') {
		return a + b;
	} else if(operation == '-') {
		return a - b;
	} else if(operation == '*') {
		return a * b;
	} else if(operation == '/') {
		return a / b;
	} else if(operation == '%') {
		return a % b;
	} else {
		return -1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Able to solve a given postfix string and return expected output
/////////////////////////////////////////////////////////////////////////////////////////////
int Postfix::solve(string postfix) {
	for (int i = 0; i < postfix.length(); i++) {
		if( postfix[i] >= 'A' && postfix[i] <= 'Z') {
			cout << "Value: Cannot be calculated" << endl;
			return -1;
		}
		if( postfix[i] == ' ') {
			continue;
		}
		if( token.isOperator(postfix[i])) {
			int b = solution.top();
			solution.pop();
			int a = solution.top();
			solution.pop();
			int value = operationType(postfix[i], a, b);
			solution.push(value);
		} else if( postfix[i] >= '0' && postfix[i] <= '9') {
			int operand = 0;
			while(i < postfix.length() && postfix[i] >= '0' && postfix[i] <= '9') {
				operand = (operand * 10) + (postfix[i] - '0');
				i++;
			}
			i--;
			solution.push(operand);
		}  	
	}
	cout << "Value: " << solution.top() << endl;
	return solution.top();
}

int main(int argc, char ** argv) {
	string infix;
	Token token;
	Postfix postfix;

	cout << "Input an expression: ";
	getline(cin, infix);
	infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	infix.erase(remove(infix.begin(), infix.end(), '\n'), infix.end());

	string tokened = token.tokenize(infix);
	cout << "Tokens: " << tokened << endl;
	if( tokened == "Invalid operator placement") {
		return 0;
	}
	string postfixed = postfix.toPostfix(tokened);
	cout << "Postfix: " << postfixed << endl;

	if( postfixed == "Error! Badly formed") {
		cout << "Value: Error! Badly formed" << endl;	
		return 0;
	} else {
		postfix.solve(postfixed);
	}
}