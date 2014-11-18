
#ifndef NODELIST_H_
#define NODELIST_H_

#include "Node.h"
using namespace std;

class NodeList {
private:
	Node* head;
public:
	NodeList();
	~NodeList();
	NodeList(const NodeList& src);
	NodeList& operator= (const NodeList& rhs);

	Node* findOrInsertNode(int key);
	bool remove(int key);
	Node* find(int key);
	bool isFound(int key);
	Node* getHead();
	bool refresh();

	friend ostream& operator<< (ostream& out, const NodeList& rhs);
};

ostream & operator << (ostream& out, const NodeList& rhs);
#endif /* NODELIST_H_ */
