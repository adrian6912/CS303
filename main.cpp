#include "infix_parser.h"
#include <iostream>
#include <string>

int main() {
	Infix_Parser inf("39*8/5+22");
	std::cout << inf.infix_parser();
	system("pause");
}
