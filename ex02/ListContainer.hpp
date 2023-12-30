#pragma once

#include <iostream>
#include "AConatiner.hpp"
#include <list>
#include <utility>

class ListContainer : public AContainer<std::list<std::pair<int, int> >, std::list<int> >
{
public:
	ListContainer();
	ListContainer(const ListContainer &listContainer);
	~ListContainer();
	ListContainer &operator=(const ListContainer &listContainer);

	void setMainChain();
	void sortPendChain();
	void checkStraggler();

private:
	void mergeTuples(std::list<std::pair<int, int> > left, std::list<std::pair<int, int> > right, std::list<std::pair<int, int> > &dest);
	std::list<int>::iterator getMainChain(int i);
	std::list<int>::iterator getPendChain(int i);
	int getFromIndex(std::list<int> list, int index);

};