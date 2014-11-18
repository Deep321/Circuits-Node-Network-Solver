
#include "ResistorList.h"

ResistorList::ResistorList() {
	resHead=NULL;
	numRes=0;
}

ResistorList::~ResistorList() {
   Resistor *currRes, *prevRes;

   currRes = resHead;
   while (currRes != NULL) {
	  prevRes = currRes;
	  currRes = currRes->getNext ();
	  delete prevRes;
   }
   resHead = NULL;  // For safety.
}


void ResistorList::insertRes (string name, double resistance, int endpoints[2])  {
   Resistor *prev = NULL;
   Resistor *curr = resHead;
   while (curr != NULL) {
      prev = curr;
      curr = curr->getNext ();
   }

   Resistor *newRes = new Resistor(name, resistance, endpoints,curr);
   // prev is NULL when we insert at the head of the list
   if (prev != NULL)
      prev->setNext (newRes);
   else
      resHead = newRes;

   this->numRes++;
}


bool ResistorList::removeRes (string name) {
   Resistor *ptr, *prev = NULL;
   // Iterate through list
   for (ptr = resHead; ptr != NULL; ptr = ptr->getNext ()){
      if (name == ptr->getName() ) {  // Found it!
         if (prev != NULL)   // Not at list start
            prev->setNext (ptr->getNext () );
         else
            this->resHead = ptr->getNext();

         this->numRes--;
         delete ptr;
         ptr=NULL;
         return true;
      }
      prev = ptr;
   }
   return false;
}


bool ResistorList::removeAll(){
	this->numRes=0;
	bool isDeleted=false;
	Resistor* ptr=resHead;
	Resistor* prev=NULL;

	if(resHead==NULL)
		return true;

	while(ptr!=NULL){
		prev=ptr;
		ptr=ptr->getNext();
		delete prev;
		isDeleted=true;
	}

	resHead=NULL;
	return isDeleted;
}


Resistor* ResistorList::findRes (string name) {
   Resistor *ptr;

   for (ptr = resHead; ptr != NULL; ptr = ptr->getNext () )
      if (name == ptr->getName() )
         return (ptr);
   return (NULL);  // Searched list without finding it.
}


void ResistorList::print(int nodeKey){
	cout << "Connections at node " << nodeKey << ": " << this->numRes << " resistor(s)" << endl;
	for (Resistor* restemp=resHead; restemp!=NULL; restemp=restemp->getNext()) {
		cout << *restemp;
	}
}

Resistor* ResistorList::getresHead(){
	return this->resHead;
}

int ResistorList::getNumRes(){
	return this->numRes;
}




