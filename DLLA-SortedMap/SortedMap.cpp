#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <utility>
using namespace std;

SortedMap::SortedMap(Relation r) {
	relation = r;
	capacity = 5;
	currentSize = 0;
	firstPoz = 1;
	nodes = new DLLANode [5];
	nodes[0].next = nodes[0].next = 0;
	nodes[0].prev = nodes[0].prev = 0;
	nodes[0].element = NULL_TPAIR;
}
// Theta(1)
TValue SortedMap::add(TKey k, TValue v) {
	DLLANode empty;
	if (currentSize == capacity - 2) {
		DLLANode* newList = new DLLANode[capacity * 2];
		capacity *= 2;
		for (int i = 0; i <= currentSize; i++)
		{
			newList[i] = nodes[i];
			nodes[i] = empty;
		}
		delete[] nodes;
		nodes = newList;
	}
	if (nodes[0].next == 0) {
		nodes[0].next = firstPoz;
		nodes[0].prev = firstPoz;
		nodes[firstPoz].next = 0;
		nodes[firstPoz].prev = 0;
		nodes[firstPoz].element.first = k;
		nodes[firstPoz].element.second = v;
	}
	else {
		int poz = nodes[0].next;
		while (poz != 0 and relation(k, nodes[poz].element.first) == false)
		{
			poz = nodes[poz].next;
		}
		if (nodes[poz].element.first == k)
		{
			TValue oldValue;
			oldValue = nodes[poz].element.second;
			nodes[poz].element.second = v;
			return oldValue;
		}
		nodes[firstPoz].next = poz;
		nodes[firstPoz].prev = nodes[poz].prev;
		nodes[firstPoz].element.first = k;
		nodes[firstPoz].element.second = v;
		nodes[nodes[poz].prev].next = firstPoz;
		nodes[poz].prev = firstPoz;
	}
	currentSize++;
	int i = 1;
	while (i <= capacity and nodes[i].next <= capacity and nodes[i].prev <= capacity and nodes[i].next >= 0 and nodes[i].prev >= 0)
		i++;
	firstPoz = i;
	return NULL_TVALUE;
}
// BC - O(1) WC-(n) O(n)
TValue SortedMap::search(TKey k) const {
	int nextPoz = nodes[0].next;
	while (nextPoz != 0 and nodes[nextPoz].element.first != k)
	{
		nextPoz = nodes[nextPoz].next;
	}
	if (nodes[nextPoz].element.first == k)
		return nodes[nextPoz].element.second;
	return NULL_TVALUE;
}
// BC - O(1) WC-(n)
TValue SortedMap::remove(TKey k) {
	if (search(k) == NULL_TVALUE)
		return NULL_TVALUE;

	int poz = nodes[0].next;
	while (nodes[poz].element.first != k)
	{
		poz = nodes[poz].next;
	}
	if (poz < firstPoz)
		firstPoz = poz;
	nodes[nodes[poz].prev].next = nodes[poz].next;
	nodes[nodes[poz].next].prev = nodes[poz].prev;
	currentSize--;
	return nodes[poz].element.second;
}
// BC - O(1) WC-(n)
int SortedMap::size() const {
	return currentSize;
}

bool SortedMap::isEmpty() const {
	return currentSize == 0;
}
//Theta(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

int SortedMap::getValueRange() const
{
	int i, minimum, maximum;
	maximum = 0;
	minimum = 999999999;
	for (i = 1; i <= size(); i++)
	{
		if (nodes[i].element.second > maximum)
			maximum = nodes[i].element.second;
		if (nodes[i].element.second < minimum)
			minimum = nodes[i].element.second;
	}
	if (isEmpty())
		return -1;

	return maximum - minimum;
}

SortedMap::~SortedMap() {
	delete[] nodes;
}
//Theta(1)