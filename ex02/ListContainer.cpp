#include "ListContainer.hpp"

ListContainer::ListContainer() : AContainer<std::list<std::pair<int, int> >, std::list<int> >(){ return; }

ListContainer::ListContainer(const ListContainer &listContainer) : AContainer<std::list<std::pair<int, int> >, std::list<int> >(listContainer){ return; }

ListContainer::~ListContainer(){ return; }

ListContainer &ListContainer::operator=(const ListContainer &listContainer) {
	(void) listContainer;
	return *this;
}

void changeIndex(int index, int nr, std::list<int> &list)
{
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);
	*it = nr;
}
void insertIndex(int index, int nr, std::list<int> &list)
{
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);
	list.insert(it, nr);
}

void ListContainer::mergeTuples(std::list <std::pair<int, int> > left, std::list <std::pair<int, int> > right,
								std::list <std::pair<int, int> > &dest) {
	while (!left.empty() && !right.empty())
	{
		if (left.front().first < right.front().first)
		{
			dest.push_back(left.front());
			left.pop_front();
		}
		else
		{
			dest.push_back(right.front());
			right.pop_front();
		}
	}
	while (!left.empty())
	{
		dest.push_back(left.front());
		left.pop_front();
	}
	while (!right.empty())
	{
		dest.push_back(right.front());
		right.pop_front();
	}
}

void ListContainer::setMainChain(){
	if (container.empty())
	{
		mainChain.push_back(holder[1]);
		holder[0] = 0;
		return;
	}
	mainChain.push_back(container.front().second);
	mainChain.push_back(container.front().first);
	pendChain.push_back(-1);
	container.pop_front();
	while (!container.empty())
	{
		mainChain.push_back(container.front().first);
		pendChain.push_back(container.front().second);
		container.pop_front();
	}
}

std::list<int>::iterator ListContainer::getMainChain(int i)
{
	std::list<int>::iterator it = mainChain.begin();
	std::advance(it, i);
	return it;
}

std::list<int>::iterator ListContainer::getPendChain(int i){
	std::list<int>::iterator it = mainChain.begin();
	std::advance(it, i);
	return it;
}

int ListContainer::getFromIndex(std::list<int> list, int index) {
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);
	if (it == list.end())
		return -1;
	return *it;
}

void ListContainer::sortPendChain() {
	if (pendChain.empty() || pendChain.size() <= 1)
		return;
	std::list<int> jacobstahl;
	getJacobstahl(&jacobstahl, pendChain.size());

	while (!jacobstahl.empty())
	{
//		std::cout << "hi\n";
		int index = jacobstahl.back() - 1;
		int nr = getFromIndex(pendChain, index);
		while (nr != -1)
		{
			int mainIndex = binarySearch(0, mainChain.size() - 1, nr, mainChain);
			insertIndex(mainIndex, nr, mainChain);
			changeIndex(index, -1, pendChain);
			index--;
			nr = getFromIndex(pendChain, index);
		}
		jacobstahl.pop_back();
	}

	std::list<int>::iterator it = pendChain.begin();
	while (it != pendChain.end() && *it == -1)
		it++;
	while (it != pendChain.end())
	{
		int mainIndex = binarySearch(0, mainChain.size() - 1, *it, mainChain);
		insertIndex(mainIndex, *it, mainChain);
		*it = -1;
		it++;
	}

}

void ListContainer::checkStraggler() {
	if (!holder[0])
		return;
	int mainIndex = binarySearch(0, mainChain.size() - 1, holder[1], mainChain);
		insertIndex(mainIndex, holder[1], mainChain);
}
