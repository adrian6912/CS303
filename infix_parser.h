#include <stack>
#include <string>

class Infix_Parser {
public:
	Infix_Parser::Infix_Parser(std::string expression) { infix = expression; }
	int infix_parser();

private:
	
	void eval_op(const std::string op);
	int precedence(const std::string thing);
	int eval_stacks();

	std::stack<int> operands;
	std::stack<std::string> operators;
	std::string infix;
};



