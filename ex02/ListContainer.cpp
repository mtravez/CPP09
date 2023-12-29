#include "ListContainer.hpp"

ListContainer::ListContainer() : AContainer<std::list<std::pair<int, int> >, std::list<int> >(){ return; }

ListContainer::ListContainer(const ListContainer &listContainer) : AContainer<std::list<std::pair<int, int> >, std::list<int> >(listContainer){ return; }

ListContainer::~ListContainer(){ return; }

ListContainer &ListContainer::operator=(const ListContainer &listContainer) {
	(void) listContainer;
	return *this;
}

void ListContainer::mergeTuples(std::list <std::pair<int, int> > left, std::list <std::pair<int, int> > right,
								std::list <std::pair<int, int> > &dest) {
//	std::for_each(left.begin(), left.end(), printTuples);
//	std::cout << std::endl;
//	std::for_each(right.begin(), right.end(), printTuples);
//	std::cout << std::endl << "--------\n";
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
//		std::cout << "#######\n";
//		std::for_each(dest.begin(), dest.end(), printTuples);
//		std::cout << "\n#######\n";
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
	std::for_each(dest.begin(), dest.end(), printTuples);
	std::cout << std::endl << "**********\n";
}

void ListContainer::setMainChain(){
	std::for_each(mainChain.begin(), mainChain.end(), printThing);
	std::cout << std::endl;
	std::for_each(pendChain.begin(), pendChain.end(), printThing);
	mainChain.push_back(container.front().second);
	mainChain.push_back(container.front().first);
	container.pop_front();
	while (container.size() > 1)
	{
		mainChain.push_back(container.front().first);
		pendChain.push_back(container.front().second);
		container.pop_front();
	}
	std::for_each(mainChain.begin(), mainChain.end(), printThing);
	std::cout << std::endl;
	std::for_each(pendChain.begin(), pendChain.end(), printThing);
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

void changeIndex(int index, int nr, std::list<int> list)
{
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);
	*it = nr;
}
void insertIndex(int index, int nr, std::list<int> list)
{
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);
	list.insert(it, nr);
}

void ListContainer::sortPendChain() {
	std::list<int> jacobstahl;
	getJacobstahl(&jacobstahl, pendChain.size());

	while (!jacobstahl.empty())
	{
		int index = jacobstahl.back() - 1;
		int nr = getFromIndex(pendChain, index);
		while (nr != -1)
		{
			int mainIndex = binarySearch(0, mainChain.size() - 1, nr, mainChain);
//			mainChain.insert(mainChain.begin() + mainIndex, nr);
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
//		mainChain.insert(mainChain.begin() + mainIndex, *it);
		insertIndex(mainIndex, nr, mainChain);
		*it = -1;
		it++;
	}
}

void ListContainer::checkStraggler() {
	if (!holder[0])
		return;
	int mainIndex = binarySearch(0, mainChain.size() - 1, holder[1], mainChain);
		insertIndex(mainIndex, nr, mainChain);
//	mainChain.insert(mainChain.begin() + mainIndex, holder[1]);
}
