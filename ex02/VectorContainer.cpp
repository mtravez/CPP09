#include "VectorContainer.hpp"

VectorContainer::VectorContainer() : AContainer<std::vector<std::pair<int, int> >, std::vector<int> >(){ return; }

VectorContainer::VectorContainer(const VectorContainer &listContainer) : AContainer<std::vector<std::pair<int, int> >, std::vector<int> >(listContainer){ return; }

VectorContainer::~VectorContainer(){ return; }

VectorContainer &VectorContainer::operator=(const VectorContainer &listContainer) {
	(void) listContainer;
	return *this;
}

void VectorContainer::mergeTuples(std::vector <std::pair<int, int> > left, std::vector <std::pair<int, int> > right,
								std::vector <std::pair<int, int> > &dest) {
	unsigned long lSize = left.size();
	unsigned long rSize = right.size();
	unsigned long l = 0, r = 0, d = 0;
	while (dest.size() < (lSize + rSize))
	{
		std::pair<int, int> hi;
		dest.push_back(hi);
	}
	while (l < lSize && r < rSize)
	{
		if (left[l].first < right[r].first)
		{
			dest[d] = left[l];
			l++;
		}
		else
		{
			dest[d] = right[r];
			r++;
		}
		d++;
	}

	while (l < lSize)
	{
		dest[d++] = left[l++];
	}
	while (r < rSize)
	{
		dest[d++] = right[r++];
	}
}

void VectorContainer::setMainChain(){
	if (container.empty())
	{
		mainChain.push_back(holder[1]);
		holder[0] = 0;
		return;
	}
	unsigned int i = 1;
	mainChain.push_back(container[0].second);
	mainChain.push_back(container[0].first);
	pendChain.push_back(-1);
	while (i < container.size())
	{
		mainChain.push_back(container[i].first);
		pendChain.push_back(container[i].second);
		i++;
	}
	while (!container.empty())
		container.pop_back();
}

int VectorContainer::getFromIndex(std::vector<int> list, int index) {
	if (index >= static_cast<int>(list.size()) || index < 0)
		return -1;
	return list[index];
}

void VectorContainer::sortPendChain() {
	if (pendChain.empty() || pendChain.size() <= 1)
		return;
	std::vector<int> jacobstahl;
	getJacobstahl(&jacobstahl, pendChain.size());

	while (!jacobstahl.empty())
	{
		int index = jacobstahl.back() - 1;
		int nr = getFromIndex(pendChain, index);
		int i = 0;
		while (nr != -1)
		{
			int mainIndex = binarySearch(0, index + i, nr, mainChain);
			mainChain.insert(mainChain.begin() + mainIndex, nr);
			pendChain[index] = -1;
			index--;
			nr = getFromIndex(pendChain, index);
			i++;
		}
		jacobstahl.pop_back();
	}
	std::vector<int>::iterator it = pendChain.begin();
	while (it != pendChain.end() && *it == -1)
		it++;
	while (it != pendChain.end())
	{
		int mainIndex = binarySearch(0, mainChain.size() - 1, *it, mainChain);
		mainChain.insert(mainChain.begin() + mainIndex, *it);
		*it = -1;
		it++;
	}
}

void VectorContainer::checkStraggler() {
	if (!holder[0])
		return;
	int mainIndex = binarySearch(0, mainChain.size() - 1, holder[1], mainChain);
	mainChain.insert(mainChain.begin() + mainIndex, holder[1]);
}
