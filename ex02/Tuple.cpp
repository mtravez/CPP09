#include "Tuple.hpp"

void printTuples(std::pair<int, int> t)
{
	std::cout << "{" << t.first << ", " << t.second << "} ";
}

void swapTuples(std::pair<int, int> &t)
{
	if (t.first < t.second)
	{
		int temp = t.first;
		t.first = t.second;
		t.second = temp;
	}
	return;
}

void printThing(int i)
{
	std::cout << i << " ";
}

void printArray(char **arr)
{
	for (int i = 0; arr && arr[i]; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}