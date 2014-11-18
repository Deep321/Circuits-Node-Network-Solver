
#ifndef RPARSER_H_
#define RPARSER_H_

#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

#define RESIS_PRECISION 2
#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

class Rparser{
private:



public:
	bool insertR(stringstream& linestream, NodeList& nodeList);
	bool modifyR(stringstream& linestream, NodeList& nodeList);
	bool printR(stringstream& linestream, NodeList& nodeList);
	bool printNode(stringstream& linestream, NodeList& nodeList);
	bool deleteR(stringstream& linestream, NodeList& nodeList);
	bool setV(stringstream& linestream, NodeList& nodeList);
	bool unsetV(stringstream& linestream, NodeList& nodeList);
	bool solve(stringstream& linestream, NodeList& nodeList);

	void parse();

	Rparser();
	~Rparser();


};


#endif /* RPARSER_H_ */
