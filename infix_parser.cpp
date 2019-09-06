#include "infix_parser.h"
#include <sstream>
#include <iostream>


int Infix_Parser::infix_parser() {

	size_t x = 0;
	size_t y = 0;
	std::stringstream number_s, operator_s;
	std::string operator_holder, operator_ext;
	int number;
	double result = 0;

	while (x < infix.size()) {
		if (!iswspace(infix[x])) {
			if (isdigit(infix[x])) {	//finds length of digit, then adds it to operands stack. Assumes no spaces between digits in a number.
				y = x;					//makes it so that we don't "lose our place"
				while (isdigit(infix[x])) {
					x++;
				}
				number_s.clear();
				number_s.str(infix.substr(y, x));
				number_s >> number;
				while (operators.top() == "++" || operators.top() == "--" || operators.top() == "!") { //check for ++, --, and/or ! operators once the number is read and evaluate immediately
					if (operators.top() == "++") {
						number++;
						operators.pop();
					}
					else if (operators.top() == "--") {
						number--;
						operators.pop();
					}
					else if (operators.top() == "!") {
						number = !number;
						operators.pop();
					}
				}

				operands.push(number);

			}

			else {								//infix[x] is NOT a digit, so it must be an operator or part of one. OR parens
				operator_s.clear();
				operator_s << infix[x];			//index[x] is a char. Convert to string so we can find in precedence array
				operator_s >> operator_holder;

				if (!isdigit(infix[x + 1]) && !iswspace(infix[x + 1])) {	//check to see if the next index is even part of an operator, otherwise skip
					operator_s.clear();							//re-use stringstream obj and convert
					operator_s << infix[x + 1];
					operator_s >> operator_ext;
					if (operator_holder == operator_ext)		//++, --, ==, &&, ||
						operator_holder += operator_ext;
					else if (operator_ext == "=")				//!=, >=, <= 
						operator_holder += operator_ext;
					x++;
				}

				eval_op(operator_holder);
			}
		}
		else
			x++;
	}
	
	return eval_stacks();
}

int Infix_Parser::precedence(const std::string thing) {

	const std::string OPERATORS_CONST[18] = { "!", "++", "--", "-", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };
	const int PRECEDENCE[18] = { 8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1 };

	return (PRECEDENCE[OPERATORS_CONST->find(thing)]);
}

void Infix_Parser::eval_op(const std::string op) {
	if (precedence(op) > precedence(operators.top()) || operators.empty() || operators.top() == "++" || operators.top() == "--" || operators.top() == "!")
		operators.push(op);
	else if (precedence(op) <= precedence(operators.top()) && operands.size() > 1) {	//will always have two operands before an operator
		int rhs = operands.top();	//"top"
		operands.pop();
		int lhs = operands.top();	//"bottom"
		operands.pop();
		
		if (operators.top() == "+") {
			operands.push(lhs + rhs);
			operators.push(op);
		}
		else if (operators.top() == "-") {
			operands.push(lhs - rhs);
			operators.push(op);
		}
		else if (operators.top() == "*") {
			operands.push(lhs * rhs);
			operators.push(op);
		}
		else if (operators.top() == "/") {
			operands.push(lhs / rhs);
			operators.push(op);
		}
		else if (operators.top() == "%") {
			operands.push(lhs % rhs);
			operators.push(op);
		}
		else if (operators.top() == "^") {
			operands.push(lhs ^ rhs);
			operators.push(op);
		}
		else if (operators.top() == ">") {
			operands.push(lhs > rhs);
			operators.push(op);
		}
		else if (operators.top() == "<") {
			operands.push(lhs < rhs);
			operators.push(op);
		}
		else if (operators.top() == ">=") {
			operands.push(lhs >= rhs);
			operators.push(op);
		}
		else if (operators.top() == "<=") {
			operands.push(lhs <= rhs);
			operators.push(op);
		}
		else if (operators.top() == "&&") {
			operands.push(lhs && rhs);
			operators.push(op);
		}
		else if (operators.top() == "||") {
			operands.push(lhs || rhs);
			operators.push(op);
		}
		else if (operators.top() == "==") {
			operands.push(lhs == rhs);
			operators.push(op);
		}
		else if (operators.top() == "!=") {
			operands.push(lhs != rhs);
			operators.push(op);
		}
	}
	return;
}

int Infix_Parser::eval_stacks() {	//operators in operator stack are in order by precedence
	while (operators.size() != 1) {
		int rhs = operands.top();	//"top"
		operands.pop();
		int lhs = operands.top();	//"bottom"
		operands.pop();

		if (operators.top() == "+") {
			operands.push(lhs + rhs);
		}
		else if (operators.top() == "-") {
			operands.push(lhs - rhs);
		}
		else if (operators.top() == "*") {
			operands.push(lhs * rhs);
		}
		else if (operators.top() == "/") {
			operands.push(lhs / rhs);
		}
		else if (operators.top() == "%") {
			operands.push(lhs % rhs);
		}
		else if (operators.top() == "^") {
			operands.push(lhs ^ rhs);
		}
		else if (operators.top() == ">") {
			operands.push(lhs > rhs);
		}
		else if (operators.top() == "<") {
			operands.push(lhs < rhs);
		}
		else if (operators.top() == ">=") {
			operands.push(lhs >= rhs);
		}
		else if (operators.top() == "<=") {
			operands.push(lhs <= rhs);
		}
		else if (operators.top() == "&&") {
			operands.push(lhs && rhs);
		}
		else if (operators.top() == "||") {
			operands.push(lhs || rhs);
		}
		else if (operators.top() == "==") {
			operands.push(lhs == rhs);
		}
		else if (operators.top() == "!=") {
			operands.push(lhs != rhs);
		}
	}

	return operands.top();
}