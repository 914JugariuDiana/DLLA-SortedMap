#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	position = m.nodes[0].next;
}
// Theta(1)
void SMIterator::first(){
	position = map.nodes[0].next;
}
// Theta(1)
void SMIterator::next(){
	if (position == 0)
		throw exception();
	position = map.nodes[position].next;
}
// Theta(1)
bool SMIterator::valid() const{
	return position != 0;
}
// Theta(1)
TElem SMIterator::getCurrent() const{
	if (position == 0) 
		throw exception();
	return map.nodes[position].element;
}
// Theta(1)

