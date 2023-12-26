#include "iostream"
#include "Date.hpp"
#include "Data.hpp"
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: wrong number of parameters." << std::endl;
		return 1;
	}
	try {
		BitcoinExchange hi;
		hi.printData(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error, could not open file.\n";
	}
	return (0);
}