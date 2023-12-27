#pragma once

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

class RPN
{
private:
	std::stack<int> stack;
	void doOperation(char c);

public:
	RPN();
	RPN(const RPN &rpn);
	~RPN();
	RPN &operator=(const RPN &rpn);
	int doStuff(std::string str);
	class WrongInputException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Error: wrong input\n";
		}
	};
	class NotEnoughNumbersInListException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Error: tried operation with 1 or 0 numbers in list\n";
		}
	};
	class WrongResultException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Error: the list has more than one number at end\n";
		}
	};
};