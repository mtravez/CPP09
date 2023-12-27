#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include "Data.hpp"
#include "Date.hpp"

class BitcoinExchange{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &bitcoinExchange);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &bitcoinExchange);

	std::string getDate(std::string string);
	float getValue(std::string value);
	void printData(std::string file);
private:
	Data data;
	std::string separator;
};

