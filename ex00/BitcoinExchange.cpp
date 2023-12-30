#include "BitcoinExchange.hpp"

std::string BitcoinExchange::getDate(std::string string) {
	std::string date;
	char data[string.size() + 1];
	char *p;
	strncpy(data, string.c_str(), sizeof(data));
	p = strtok(data, separator.c_str());
	try {
		if (Date::isDateCorrect(p))
			date.assign(p);
		else
		{
			std::cerr << "Error: bad input => " << p << std::endl;
			return "";
		}
	}
	catch (std::exception &e) {
		std::cerr << e.what();
		return "";
	}
	return date;
}

float BitcoinExchange::getValue(std::string value) {
	char data[value.size() + 1];
	char *p;

	strncpy(data, value.c_str(), sizeof(data));
	p = strtok(data, separator.c_str());
	p = strtok(NULL, separator.c_str());
	float exRate = strtod(p, NULL);
	if (errno == ERANGE)
	{
		std::cerr << "Error: wrong input => " << p << std::endl;
		return -1.0;
	}
	if (exRate < 0)
	{
		std::cerr << "Error: not a positive number" << std::endl;
		return -1.0;
	}
	if (!Date::isNumber(p, true))
	{
		std::cerr << "Error: wrong input => " << p << std::endl;
		return -1.0;
	}
	if (exRate > 1000)
	{
		std::cerr << "Error: too large a number" << std::endl;
		return -1.0;
	}
	return exRate;
}

void BitcoinExchange::printData(std::string file) {
	std::ifstream inputFile(file.c_str());
	if (!inputFile)
		throw (Data::UnavailableDataException());
	std::string line;
	if (!std::getline(inputFile, line))
	{
		inputFile.close();
		return;
	}
	while (std::getline(inputFile, line)) {
		std::string date = getDate(line);
		if (date.empty())
			continue;
		float value = getValue(line);
		if (value < 0)
			continue;
		Data::iterator it = this->data.getClosest(date);
		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	}
}

BitcoinExchange::BitcoinExchange() : separator(" | ") {return;}

BitcoinExchange::~BitcoinExchange() {return;}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &bitcoinExchange) : data(bitcoinExchange.data), separator(" | "){return;}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &bitcoinExchange) {
	(void) bitcoinExchange;
	return (*this);
}