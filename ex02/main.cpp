#include "ListContainer.hpp"
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	PmergeMe<ListContainer> hello;
//	PmergeMe<VectorContainer> hello;
	hello.pMergeMe(&(argv[1]));
	return 0;
}