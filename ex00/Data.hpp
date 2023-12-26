#pragma once

#include <iostream>
#include <cstring>
#include <map>
#include <fstream>

class Data : public std::map <std::string, float>
{
public:
	Data();
	Data(const Data &data);
	~Data();
	Data &operator=(const Data &data);

	Data::iterator getClosest(std::string key);
	class UnavailableDataException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "UnavailableDataException: database is missing or has the wrong name";
		}
	};
};