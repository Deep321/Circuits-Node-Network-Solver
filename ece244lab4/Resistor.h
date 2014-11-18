
#ifndef RESISTOR_H
#define RESISTOR_H

#include <iostream>
#include <iomanip>
using namespace std;

class Resistor{
private:
   Resistor *next;
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to

public:

   Resistor();
   Resistor(string name_,double resistance_,int endpoints_[2],Resistor *next);

   ~Resistor();

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance
   int getEndpointNodeID1() const;//returns the first node id
   int getEndpointNodeID2() const;//returns the second node id

   int getRIndex();
   void setResistance (double resistance_);

   int getrIndex ();
   void setrIndex (int _key);
   Resistor* getNext ();
   void setNext (Resistor *_next);

   int getOtherNodeId(int nodeid1) const;

   void print ();
   friend ostream& operator<<(ostream&,const Resistor&);
};

ostream& operator<<(ostream&,const Resistor&);

#endif	/* RESISTOR_H */

