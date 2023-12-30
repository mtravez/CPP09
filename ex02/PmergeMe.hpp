#pragma once

#include "AConatiner.hpp"
#include "ListContainer.hpp"
#include "VectorContainer.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits.h>

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
		try{
			splitTuples(arr);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what();
			return;
		}
		std::cout << "Before:\t";
		printArray(arr);
		container.sortTuples();
		container.mergeSortTuples(container.getContainer());
		container.setMainChain();
		container.sortPendChain();
		container.checkStraggler();
		std::cout << "After:\t";
		container.printChain();
	}

	class NotValidInputException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Error: wrong input\n";
		}
	};

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
			if (!isNumber(arr[i]) || atol(arr[i]) > INT_MAX)
				throw (NotValidInputException());
			i++;
		}
		return true;
	}

};

