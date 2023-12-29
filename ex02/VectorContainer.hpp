#pragma once

#include <iostream>
#include "AConatiner.hpp"
#include <list>
#include <tuple>
#include <utility>

class VectorContainer : public AContainer<std::vector<std::pair<int, int> >, std::vector<int> >
{
public:
	VectorContainer();
	VectorContainer(const VectorContainer &listContainer);
	~VectorContainer();
	VectorContainer &operator=(const VectorContainer &listContainer);
	void setMainChain();
	void sortPendChain();
	void checkStraggler();

private:
	void mergeTuples(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right, std::vector<std::pair<int, int> > &dest);
	std::vector<int>::iterator getMainChain(int i);
	std::vector<int>::iterator getPendChain(int i);
	int getFromIndex(std::vector<int> list, int index);

};