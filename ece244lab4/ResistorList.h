
#ifndef RESISTORLIST_H_
#define RESISTORLIST_H_


#include "Resistor.h"
using namespace std;

class ResistorList {
private:
	Resistor* resHead;
	int numRes;
public:
   void insertRes (string name, double resistance, int endpoints[2]);
   bool removeRes (string name);
   bool removeAll();
   Resistor *findRes (string name);
   void print(int nodeKey);
   int getNumRes();

   Resistor* getresHead();

	ResistorList();
	~ResistorList();
};

#endif /* RESISTORLIST_H_ */
