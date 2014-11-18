
#include "Node.h"

Node::Node (){
	key = 0;
	voltage=0;
	next = NULL;
	resList=new ResistorList();
	isSet=false;
}


Node::Node (int _key, Node* _next){
	voltage=0;
	key = _key;
	next = _next;
	resList=new ResistorList();
	isSet=false;
}

Node::~Node() {
	delete this->resList;//TODO
}


int Node::getKey () {
   return (key);
}


void Node::setKey (int _key) {
   key = _key;
}


Node* Node::getNext () {
   return (next);
}


void Node::setNext (Node* _next) {
   next = _next;
}


double Node::getVoltage(){
	return this->voltage;
}


void Node::setVoltage(double _voltage){
	this->voltage=_voltage;
}


void Node::unsetVoltage(){
	this->voltage=0.0;
}


bool Node::getIsSet(){
	return this->isSet;
}


void Node::setIsSet(bool isSet){
	this->isSet=isSet;
}


ostream& operator<< (ostream& out, Node rhs) {
   out << rhs.getKey();  // Not friend; only use public
   return (out);
}

void Node::print (){
	resList->print(key);
}


ResistorList* Node::getResList(){
	return this->resList;
}


void Node::insertRes (string name, double resistance, int endpoints[2]){
	this->resList->insertRes(name,resistance,endpoints);
}


bool Node::removeRes (string name){
	return this->resList->removeRes(name);
}


bool Node::removeAll(){
	return this->resList->removeAll();
}


Resistor* Node::findRes (string name){
	return this->resList->findRes(name);
}
