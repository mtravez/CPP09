#include "ListContainer.hpp"
#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	PmergeMe<ListContainer> sorting1;
	clock_t startTime = clock();
	sorting1.pMergeMe(&(argv[1]));
	clock_t endTime = clock();
	double elapsedTime = static_cast<double>(endTime - startTime) * 1000000 / CLOCKS_PER_SEC;
//
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : " << std::fixed << std::setprecision(5) << elapsedTime << " us\n";

	PmergeMe<VectorContainer> sorting2;
	startTime = clock();
	sorting2.pMergeMe(&(argv[1]));
	endTime = clock();
	elapsedTime = static_cast<double>(endTime - startTime) * 1000000 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << std::fixed << std::setprecision(5) << elapsedTime << " us\n";
	return 0;
}