#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <tuple>
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
		std::for_each(temp1.begin(), temp1.end(), printTuples);
		std::cout << std::endl;
		printTuples(temp1.back());
		std::cout << "--------\n";
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

protected:
	T container;
	X mainChain;
	X pendChain;
	int holder[2];

	virtual void mergeTuples(T left, T right, T &dest)
	{
//		unsigned long lSize = left.size();
//		unsigned long rSize = right.size();
//		unsigned long l = 0, r = 0, d = 0;
//		while (l < lSize && r < rSize)
//		{
//			if (left[l] < right[r])
//			{
//				dest[d] = left[l];
//				l++;
//			}
//			else
//			{
//				dest[d] = right[r];
//				r++;
//			}
//			d++;
//		}
//
//		while (l < lSize)
//		{
//			dest[d++] = left[l++];
//		}
//		while (r < rSize)
//		{
//			dest[d++] = right[r++];
//		}
		(void) left;
		(void) right;
		(void) dest;
	}

	int *getJacobstahl(unsigned int n)
	{
		int jacobstahl[n];
		if (jacobstahl <= 2)
			return NULL;
		jacobstahl[0] = 0;
		jacobstahl[1] = 1;
		for (int i = 2; i < n; i++)
		{
			jacobstahl[i] = jacobstahl[i - 1] + 2 * jacobstahl[i - 2];
		}
		return &jacobstahl;
	}

};