

#include "Resistor.h"

Resistor::Resistor(){
   this->next=NULL;
   this->resistance=0;
   this->name="";
}

Resistor::Resistor(string name_,double resistance_,int endpoints_[2],Resistor*next){
	this->name = name_;
	this->resistance=resistance_;
	this->endpointNodeIDs[0]=endpoints_[0];
	this->endpointNodeIDs[1]=endpoints_[1];
	this->next=next;
}

Resistor::~Resistor() {

}

string Resistor::getName() const{
	return this->name;
}

void Resistor::setResistance (double resistance_){
	this->resistance = resistance_;
}

double Resistor::getResistance() const{
	return this->resistance;
}

int Resistor::getEndpointNodeID1() const{
	return this->endpointNodeIDs[0];
}

int Resistor::getEndpointNodeID2() const{
	return this->endpointNodeIDs[1];
}


Resistor* Resistor::getNext () {
   return next;
}


void Resistor::setNext (Resistor* _next) {
   this->next = _next;
}


int Resistor::getOtherNodeId(int nodeid1) const{
	if(this->endpointNodeIDs[0]==nodeid1)
		return this->endpointNodeIDs[1];
	else
		return this->endpointNodeIDs[0];
}


ostream& operator<<(ostream& out,const Resistor& resistor){
	out << left << setw(20) << setfill(' ') << resistor.name << " " << right << setw(8) << setfill(' ') << resistor.resistance
	        		<< " Ohms " << resistor.endpointNodeIDs[0] << " -> " << resistor.endpointNodeIDs[1] << endl;
	return out;
}

