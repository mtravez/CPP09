#pragma once

#include "AConatiner.hpp"
#include "ListContainer.hpp"
#include "VectorContainer.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>


template <typename T>
class PmergeMe
{
public:
	T container;

	PmergeMe(){};
	PmergeMe(const PmergeMe &pmergeMe) : container(pmergeMe.container){};
	PmergeMe(T container) : container(container){};
	~PmergeMe(){};

	void splitTuples(char **arr) {
		if (!checkNumbers(arr))
			return;
		int i = 0;
		while (arr[i]){
			container.pushNumber(atoi(arr[i]));
			i++;
		}
	}

	void pMergeMe(char **arr)
	{
		splitTuples(arr);
		container.sortTuples();
		container.mergeSortTuples(container.getContainer());
		container.setMainChain();
	}

private:
	bool isNumber(char *number)
	{
		int i = 0;
		while (number && number[i])
		{
			if (!isdigit(number[i]))
				return false;
			i++;
		}
		if (number)
			return true;
		return false;
	}

	bool checkNumbers(char **arr)
	{
		int i = 0;
		while (arr && arr[i])
		{
			if (!isNumber(arr[i]) || atol(arr[i]) > INT32_MAX)
				return false;
			i++;
		}
		return true;
	}

};

