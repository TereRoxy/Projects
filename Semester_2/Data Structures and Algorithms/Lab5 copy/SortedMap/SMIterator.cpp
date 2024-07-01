#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;


//BC=WC=TC=Theta(n), n - number of nodes in the tree
SMIterator::SMIterator(const SortedMap& m) : map(m){
	current = 0;
	nrElem = 0;
	nodes = new TElem[map.size()]; //create an array of fixed size
	buildTraversalOrder(map.root); //build the traversal order of the nodes
}

//BC=WC=TC=Theta(1)
void SMIterator::first(){
	current = 0;
}


//BC=WC=TC=Theta(1)
void SMIterator::next(){
	if (!valid()) {
		throw exception();
	}
	current++;
}

//BC=WC=TC=Theta(1)
bool SMIterator::valid() const{
	return current < nrElem;
}

//BC=WC=TC=Theta(1)
TElem SMIterator::getCurrent() const{
	if (valid()) {
		return nodes[current];
	}
	throw exception();
}

//BC=WC=TC=Theta(nrElements)
void SMIterator::buildTraversalOrder(SortedMap::Node* node)
{
	if (node == NULL) {
		return;
	}
	buildTraversalOrder(node->left);
	nodes[nrElem++] = TElem(node->info.first, node->info.second);
	buildTraversalOrder(node->right);
}

//BC=WC=TC=Theta(n), n - number of nodes in the tree
SMIterator::~SMIterator()
{
	delete[] nodes;
}