#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include "Tuple.hpp"

template <typename T, typename X>
class AContainer{
public:
	AContainer() {holder[0] = 0; holder[1] = 0;};
	AContainer(const AContainer &container){(void) container;};
	virtual ~AContainer(){};
	AContainer &operator=(const AContainer& container){
		(void) container;
		return *this;
	};

	T &getContainer(){
		return this->container;
	}

	void printChain()
	{
		std::for_each(mainChain.begin(), mainChain.end(), printThing);
		std::cout << std::endl;
	}

	virtual void pushNumber(int nr){
		if (holder[0] != 0)
		{
			std::pair<int, int>  tup;
			tup.first = holder[1];
			holder[0] = 0;
			tup.second = nr;
			container.push_back(tup);
		}
		else
		{
			holder[0] = 1;
			holder[1] = nr;
		}
	}

	virtual void sortTuples()
	{
		std::for_each(container.begin(), container.end(), swapTuples);
	}

	virtual void mergeSortTuples(T &toSort)
	{
		int size = toSort.size();
		if (size <= 1)
			return;
		T temp1;
		T temp2;
		int i = 0;
		while (i < (size / 2))
		{
			temp1.push_back(toSort.back());
			toSort.pop_back();
			i++;
		}
		while (i < size)
		{
			temp2.push_back(toSort.back());
			toSort.pop_back();
			i++;
		}
		mergeSortTuples(temp1);
		mergeSortTuples(temp2);
		mergeTuples(temp1, temp2, toSort);
	}

	virtual void setMainChain(){
		while (container.size() > 1)
		{
			mainChain.push_back(container.back().first);
			pendChain.push_back(container.back().second);
			container.pop_back();
		}
		mainChain.push_back(container.back().first);
		mainChain.push_back(container.back().second);
		container.pop_back();
		std::for_each(mainChain.begin(), mainChain.end(), printThing);
		std::cout << std::endl;
		std::for_each(pendChain.begin(), pendChain.end(), printThing);
	}

	int binarySearch(int min, int max, int nr, X list)
	{
		if (min > max)
			return min;
		int mid = min + ((max - min) / 2);
		if (getFromIndex(list, mid) == nr)
			return mid;
		if (getFromIndex(list, mid) < nr)
			return binarySearch(mid + 1, max, nr, list);
		return binarySearch(min, mid - 1, nr, list);
	}

	virtual void sortPendChain()
	{
	}

	virtual void checkStraggler()
	{
	}

protected:
	T container;
	X mainChain;
	X pendChain;
	int holder[2];

	virtual void mergeTuples(T left, T right, T &dest)
	{
		(void) left;
		(void) right;
		(void) dest;
	}

	void getJacobstahl(X *jacobstahl, int n)
	{
		int arr[n];
		int i;
		arr[0] = 0;
		arr[1] = 1;
		for (i = 2; i < n; i++)
		{
			arr[i] = arr[i - 1] + 2 * arr[i - 2];
			if (arr[i] > n)
			{
				--i;
				break;
			}
			if (arr[i] == n)
				break;
		}
		if (n == i)
			--i;
		while (i > 2)
			jacobstahl->push_back(arr[i--]);
	}

	virtual int getFromIndex(X list, int index)
	{
		(void) list;
		return index;
	}
};