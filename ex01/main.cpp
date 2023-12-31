#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: wrong number of arguments\n";
		return 1;
	}

	RPN rpn;
	try {
		std::cout << rpn.doStuff(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what();
		return 1;
	}
	return 0;
}