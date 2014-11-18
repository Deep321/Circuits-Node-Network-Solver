
#include "NodeList.h"

NodeList::NodeList(){
	this->head=NULL;
}

NodeList::~NodeList ()
{
   Node *currNode, *prevNode;

   currNode = head;
   while (currNode != NULL) {
      prevNode = currNode;
      currNode = currNode->getNext ();
      delete prevNode;
   }
   head = NULL;  // For safety.
}

NodeList::NodeList (const NodeList& src) {
   Node *srcPtr, *curr;
   Node *prev = NULL;

   for (srcPtr = src.head; srcPtr != NULL;
         srcPtr = srcPtr->getNext ()) {
      curr = new Node (srcPtr->getKey (), NULL );
      if (prev != NULL)
         prev->setNext (curr);
      else
         head = curr;

      prev = curr;
   }
}

/*-------------node management----------------*/

Node* NodeList::findOrInsertNode (int key)  {
   Node *prev = NULL;
   Node *curr = head;
   while (curr != NULL && key >= curr->getKey () ) {
	  if(key==curr->getKey())//if found the node
		  return curr;
	  prev = curr;
	  curr = curr->getNext ();
   }

   //if not found, insert
   Node *newNode = new Node (key, curr);
   if (prev != NULL){
	  prev->setNext (newNode);
	  return prev->getNext();
   }else{//if inserting at head
	  head = newNode;
	  return head;
   }
}


bool NodeList::remove (int key) {
   Node *ptr, *prev = NULL;
   // Iterate through NodeList
   for (ptr = head; ptr != NULL; ptr = ptr->getNext ()){
      if (key == ptr->getKey () ) {  // Found it!
         if (prev != NULL)   // Not at NodeList start
            prev->setNext (ptr->getNext () );
         else
            head = ptr->getNext();

         delete ptr;
         return true;
      }
      prev = ptr;
   }
   return false;
}



Node* NodeList::find (int key) {
   Node *ptr;

   for (ptr = head; ptr != NULL; ptr = ptr->getNext () ) {
      if (key == ptr->getKey () )
         return (ptr);
      if (key < ptr->getKey () )
         return (NULL);
   }
   return (NULL);  // Searched NodeList without finding it.
}

bool NodeList::isFound(int key){
	Node *ptr;

	for (ptr = head; ptr !=NULL; ptr = ptr->getNext()) {
		if(key==ptr->getKey())
			return true;
		else if(key<ptr->getKey())
			return false;
	}
	return false;
}


NodeList& NodeList::operator = (const NodeList& rhs) {
   Node *rhsPtr, *curr, *prev;

   if (this == &rhs)  // self copy, a = a
      return (*this);

   // Free old lhs NodeList (calling object).
   curr = head;
   while (curr != NULL)  {
      prev= curr;
      curr = curr->getNext ();
      delete prev;
   }
   // Make a deep copy of rhs.
   prev = NULL;
   for (rhsPtr = rhs.head; rhsPtr != NULL;
        rhsPtr = rhsPtr->getNext () ) {
      curr= new Node (rhsPtr->getKey (), NULL );

      if (prev != NULL)
         prev->setNext (curr);
      else
         head = curr;

      prev= curr;
   }

   return (*this);  // For a = b = c (chaining)
}

Node* NodeList::getHead(){
	return this->head;
}

bool NodeList::refresh(){
	bool isRefreshed=false;
	Node*temp;
	for(temp=this->head; temp!=NULL; temp=temp->getNext())
		if(temp->getResList()->getresHead()==NULL){
			this->remove(temp->getKey());
			isRefreshed=true;
		}
	return isRefreshed;
}


ostream & operator << (ostream& out, const NodeList& rhs) {
   Node *ptr;

   for (ptr= rhs.head; ptr != NULL; ptr = ptr->getNext() )
      out << ptr->getKey() << " "; // Using operator<< (os, Node)

   out << endl;

   return (out);
   // To allow chaining:  cout << NodeList1 << NodeList2 << endl;
}
