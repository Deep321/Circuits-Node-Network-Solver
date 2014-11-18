

#include "Rparser.h"

//helper functions
double KCLsolver(Node& node, NodeList& nodeList);
bool isDouble(string input);
bool isInt(string input);
int stringToInt(string input);
double stringToDouble(string input);
bool isTooManyTest(stringstream& linestream);

//error messages
void invalidCommandErrMsg();
void invalidArgErrMsg();
void negResArgErrMsg();
void resNameErrMsg();
void sameNodeErrMsg(int nodeID);
void tooManyArgErrMsg();
void tooFewArgErrMsg();
void nodeFullErrMsg();
void nameNotFoundErrMsg(string name);
void resArrayFullErrMsg();
void noNodeVoltSetErrMsg();

Rparser::Rparser(){

}


Rparser::~Rparser(){

}


bool Rparser::insertR(stringstream& linestream, NodeList& nodeList){

    string name;
    double resistance = 0.0;
    string resistanceString;
    int nodeID[2];
    string nodeIDString1, nodeIDString2;

    //line reading starts here

    //read name
	linestream >> name;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else if(name.compare("all")==0){
		resNameErrMsg();
		return false;
	}

    //read resistance
	linestream >> resistanceString;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else{//if nothing fails
		if(isDouble(resistanceString)){
			resistance = stringToDouble(resistanceString);
			if(resistance < 0){
				negResArgErrMsg();
				return false;
			}
		}else{
			invalidArgErrMsg();
			return false;
		}
	}

    //read nodeID1
	linestream >> nodeIDString1;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else{//if nothing fails
		if(isInt(nodeIDString1))
			nodeID[0] = stringToInt(nodeIDString1);
		else{
			invalidArgErrMsg();
			return false;
		}
	}

    //read nodeID2
	linestream >> nodeIDString2;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else{//if nothing fails
		if(isInt(nodeIDString2))
			nodeID[1] = stringToInt(nodeIDString2);
		else{
			invalidArgErrMsg();
			return false;
		}
	}

    //line reading ends here
    //other possible error checking goes here
	if(nodeID[0] == nodeID[1]){
		sameNodeErrMsg(nodeID[0]);
		return false;
	}

    if(isTooManyTest(linestream)){
        tooManyArgErrMsg();
        return false;
    }

    //house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }

    //insert Resistor
    cout << fixed << setprecision(RESIS_PRECISION) << "Inserted: resistor " << name << " " << resistance << " Ohms " << nodeID[0] << " -> " << nodeID[1] << endl;//Ohm(s)

    nodeList.findOrInsertNode(nodeID[0])->insertRes(name,resistance,nodeID);
    nodeList.findOrInsertNode(nodeID[1])->insertRes(name,resistance,nodeID);

    return true;
}


bool Rparser::modifyR(stringstream& linestream,NodeList& nodeList){

    string name;
    string resistanceString;
    double resistance=0.0;

    //line reading starts from here
    //read name
	linestream >> name;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else if(name.compare("all")==0){
		resNameErrMsg();
		return false;
	}

    //read resistance
	linestream >> resistanceString;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else{//if nothing fails
		if(isDouble(resistanceString)){
			resistance = stringToDouble(resistanceString);
			if(resistance < 0){
				negResArgErrMsg();
				return false;
			}
		}else{
			invalidArgErrMsg();
			return false;
		}
	}

    if(isTooManyTest(linestream)){
        tooManyArgErrMsg();
        return false;
    }

    //house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }

    //modify and printing

	for(Node*nodeTemp=nodeList.getHead(); nodeTemp!=NULL; nodeTemp=nodeTemp->getNext())
		for(Resistor*resTemp=nodeTemp->getResList()->getresHead(); resTemp!=NULL; resTemp=resTemp->getNext())
			if(resTemp->getName()==name){
				cout << fixed << setprecision(2) << "Modified: resistor " << name << " from " << resTemp->getResistance() << " Ohms to " << resistance << " Ohms" << endl;
				resTemp->setResistance(resistance);
				return true;
			}
	nameNotFoundErrMsg(name);
	return false;
}


bool Rparser::printR(stringstream& linestream,NodeList& nodeList){

    string name;
    bool isAll=false;

    //read name
	linestream >> name;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else if(name.compare("all")==0){
		isAll=true;
	}

    //if there are too many args
    if(isTooManyTest(linestream)){
        tooManyArgErrMsg();
        return false;
    }
    //house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }
    //printing
    if(isAll){
    	cout << "Print: all\n";//need not be implemented in lab4
    }else{
    	cout << "Print: " << endl;

    	for(Node*nodeTemp=nodeList.getHead(); nodeTemp!=NULL; nodeTemp=nodeTemp->getNext())
    		for(Resistor*resTemp=nodeTemp->getResList()->getresHead(); resTemp!=NULL; resTemp=resTemp->getNext())
    			if(resTemp->getName()==name){
    				cout << *resTemp;
    				return true;
    			}
    	nameNotFoundErrMsg(name);
    }
    return false;
}


bool Rparser::printNode(stringstream& linestream,NodeList& nodeList){

    string nodeIDString;
    int nodeID;
    bool isAll=false;

    //read nodeID
	linestream >> nodeIDString;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else{//if nothing fails
		if(isInt(nodeIDString)){
			nodeID = stringToInt(nodeIDString);
		}else if(nodeIDString.compare("all")==0)
			isAll=true;
		else{
			invalidArgErrMsg();
			return false;
		}
	}

    if(isTooManyTest(linestream)){
        tooManyArgErrMsg();
        return false;
    }

    //house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }

    //printing
     if(isAll){
        cout << "Print:" << endl;
        for(Node*tempnode=nodeList.getHead(); tempnode!=NULL; tempnode=tempnode->getNext())
        	tempnode->print();
     }else{
        cout << "Print:" << endl;
        nodeList.findOrInsertNode(nodeID)->print();
     }
     return true;
}


bool Rparser::deleteR(stringstream& linestream,NodeList& nodeList){

    string name;
    bool isAll=false;

    //read name
	linestream >> name;
	if(linestream.fail()){
		if(linestream.eof()){
			tooFewArgErrMsg();
			return false;
		}
		else{
			invalidArgErrMsg();
			return false;
		}
	}else if(name.compare("all")==0){
		isAll=true;
	}

    if(isTooManyTest(linestream)){
        tooManyArgErrMsg();
        return false;
    }
    //house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }
    //error checking and printing
    if(isAll){
    	bool isDeleted=false;
    	for(Node*nodeTemp=nodeList.getHead(); nodeTemp!=NULL; nodeTemp=nodeTemp->getNext())
			if(nodeTemp->removeAll()){
				isDeleted=true;
			}
    	if(isDeleted){
			cout << "Deleted: all resistors" << endl;
			nodeList.refresh();
    	return true;
    	}
    	return true;//case when no resistor at all
    }
    else{
    	bool isDeleted=false;
    	for(Node*nodeTemp=nodeList.getHead(); nodeTemp!=NULL; nodeTemp=nodeTemp->getNext())
    		if(nodeTemp->removeRes(name)){
    			isDeleted=true;
    		}
    	if(isDeleted){
    		cout << "Deleted: resistor " << name << endl;
    		nodeList.refresh();
    		return true;
    	}else
    		nameNotFoundErrMsg(name);
    }
    return false;
}

bool Rparser::setV(stringstream& linestream, NodeList& nodeList){
	int nodeID;
	double voltage;
	linestream >> nodeID >> voltage;

	Node* tempNode=nodeList.findOrInsertNode(nodeID);
	tempNode->setVoltage(voltage);
	tempNode->setIsSet(true);
	cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;
	return true;
}


bool Rparser::unsetV(stringstream& linestream, NodeList& nodeList){
	int nodeID;
	linestream >> nodeID;

	Node* tempNode=nodeList.findOrInsertNode(nodeID);
	tempNode->unsetVoltage();
	tempNode->setIsSet(false);
	cout << "Unset: the solver will determine the voltage of node " << nodeID  << endl;
	return true;
}


bool Rparser::solve(stringstream& linestream, NodeList& nodeList){
    double maxChange;
    bool isNoVoltSet=true;

	//house keeping, clear stream, ignore the rest
    if(!linestream.eof()){
        linestream.clear();
        linestream.ignore(10000,'\n');
    }

    //initialize the voltage of all nodes without a setV Voltage to 0
    Node* temp;
    for(temp=nodeList.getHead(); temp!=NULL; temp=temp->getNext()){
    	if(!temp->getIsSet())
    		temp->setVoltage(0);
    	else
    		isNoVoltSet=false;
    }

    if(isNoVoltSet){
    	noNodeVoltSetErrMsg();
    	return false;
    }

    //converge solution
    do{
    	maxChange=0.0;
    	Node* tempNode;
    	for(tempNode=nodeList.getHead(); tempNode!=NULL; tempNode=tempNode->getNext()){
    		if(!tempNode->getIsSet()){
    			double voltToSet=KCLsolver(*tempNode,nodeList);
    			double voltChange=abs(voltToSet-(tempNode->getVoltage()));
    			tempNode->setVoltage(voltToSet);
    			if(voltChange>maxChange)
    				maxChange=voltChange;
    		}
    	}
    }while(maxChange>=MIN_ITERATION_CHANGE);


    cout << " Solve:\n";
    for(temp=nodeList.getHead(); temp!=NULL; temp=temp->getNext()){
    	cout << "  Node " << temp->getKey() << ": " << temp->getVoltage() << " V" << endl;
    }

	return true;
}


//helper functions

double KCLsolver(Node& node, NodeList& nodeList){
	double numerator=0.0;
	double denominator=0.0;

	Resistor* tempRes;

	for(tempRes=node.getResList()->getresHead(); tempRes!=NULL; tempRes=tempRes->getNext()){
		denominator+=1/(tempRes->getResistance());
		Node*otherNode=nodeList.find(tempRes->getOtherNodeId(node.getKey()));
		numerator+=(otherNode->getVoltage())/(tempRes->getResistance());
	}

	return (numerator/denominator);
}

bool isDouble(string input){
    bool isDouble = true;
    double doubleConverted = 0.0;

    stringstream strm;
    strm << input;
    strm >> doubleConverted;
    if(strm.fail() | (!strm.eof())){
        isDouble=false;
    }
    return isDouble;
}

bool isInt(string input){
    bool isInt = true;
    int intConverted = 0;

    stringstream strm;
    strm << input;
    strm >> intConverted;
    if (strm.fail() | (!strm.eof())){
        isInt = false;
    }
    return isInt;
}

int stringToInt(string input){//convert using stringstream
    int intConverted = 0;
    stringstream strm;

    strm << input;
    strm >> intConverted;
    return intConverted;
}

double stringToDouble(string input){
    double doubleConverted=0.0;
    stringstream sstrm;

    sstrm << input;
    sstrm >> doubleConverted;
    if(doubleConverted== (-0))
        doubleConverted = 0;
    return doubleConverted;
}

bool isTooManyTest(stringstream& linestream){
    string testString;
    linestream >> testString;
    if(linestream.fail())
        return false;
    else
        return true;
}

//error messages
void maxValErrMsg(){
	cout << "Error: maxVal arguments must be greater than 0" << endl;
}

void invalidCommandErrMsg(){
    cout << "Error: invalid command" << endl;
}

void invalidArgErrMsg(){
    cout << "Error: invalid argument" << endl;
}

void negResArgErrMsg(){
    cout << "Error: negative resistance" << endl;
}

void resNameErrMsg(){
    cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
}

void sameNodeErrMsg(int nodeID){
    cout << "Error: both terminals of resistor connect to node " << nodeID << endl;
}

void tooManyArgErrMsg(){
    cout << "Error: too many arguments" << endl;
}

void tooFewArgErrMsg(){
    cout << "Error: too few arguments" << endl;
}

void nodeFullErrMsg(){
	cout << "Error: node is full" << endl;
}

void nameNotFoundErrMsg(string name){
	cout << "Error: resistor " << name << " not found" << endl;
}

void resArrayFullErrMsg(){
	cout << "Error: resistor array is full" << endl;
}

void noNodeVoltSetErrMsg(){
	cout << "Error: no nodes have their voltage set" << endl;
}
