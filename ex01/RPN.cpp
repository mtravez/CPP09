#include "RPN.hpp"

RPN::RPN() {return;}

RPN::RPN(const RPN &rpn) : stack(rpn.stack){ return; }

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rpn) {
//	this->stack.c = rpn.stack.c;
	(void) rpn;
	return *this;
}

void RPN::doOperation(char c)
{
	char ops[] = {'*', '+', '-', '/'};
	int i = -1;
	while (ops[++i])
		if (c == ops[i])
			break;
	int a = stack.top();
	stack.pop();
	int b = stack.top();
	stack.pop();
	switch (i) {
		case 0:
			stack.push(a * b);
			break;
		case 1:
			stack.push(a + b);
			break;
		case 2:
			stack.push(b - a);
			break;
		case 3:
			if (a == 0)
				throw (WrongInputException());
			stack.push(b / a);
			break;
		default:
			throw (WrongInputException());
	}
}

int RPN::doStuff(std::string str) {
	std::stringstream ss(str);

	std::string word;
	while (!stack.empty())
		stack.pop();
	while (ss >> word)
	{
		if (word.length() > 1)
			throw (WrongInputException());
		if (isdigit(word[0]))
		{
			stack.push(atoi(word.c_str()));
		}
		else
		{
			if (stack.size() < 2)
				throw (NotEnoughNumbersInListException());
			doOperation(word[0]);
		}
	}
	if (stack.size() != 1)
		throw (WrongResultException());
	return stack.top();
}