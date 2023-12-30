#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>

class Date {
public:
	static bool isNumber(char *number, bool isDouble);
	static bool isDateCorrect(std::string date);
	class WrongDateException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "WrongDateException: the given date is not valid";
		}
	};

	class WrongFormatException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Error: date must be in format YYYY-MM-DD";
		}
	};
private:
	Date();
	~Date();
};
