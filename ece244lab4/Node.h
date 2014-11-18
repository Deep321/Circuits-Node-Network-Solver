
#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5

#include "ResistorList.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

class Node{
private:
   int key;
   double voltage;
   bool isSet;
   Node* next;
   ResistorList* resList;

public:
   Node();
   ~Node();

   Node (int _key, Node *_next);
   int getKey ();
   void setKey (int _key);
   Node* getNext ();
   void setNext (Node *_next);
   double getVoltage();
   void setVoltage(double _voltage);
   void unsetVoltage();
   bool getIsSet();
   void setIsSet(bool isSet);
   ResistorList* getResList();

   void insertRes (string name, double resistance, int endpoints[2]);
   bool removeRes (string name);
   bool removeAll();
   Resistor* findRes (string name);
   void print ();
};

#endif	/* NODE_H */

