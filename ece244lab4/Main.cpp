
#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"
#include "NodeList.h"
#include "ResistorList.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


int main (){

	NodeList nodeList;

	int rIndexCount=0;

	Rparser rnetParser;
	string inputString;//user input


	cout << "> ";//ready to receive inputs
	getline (cin, inputString);

	while ( !cin.eof () ) {

		stringstream linestream(inputString);
		string command;
		bool isInputCorrect=true;
		linestream >> command;

		if(command.compare("insertR")==0){
			Resistor resistor;
			if(rnetParser.insertR(linestream,nodeList)){

			}

		}else if(command.compare("modifyR")==0){
			isInputCorrect=rnetParser.modifyR(linestream,nodeList);
		}else if(command.compare("printR")==0){
			isInputCorrect=rnetParser.printR(linestream,nodeList);
		}else if(command.compare("printNode")==0){
			isInputCorrect=rnetParser.printNode(linestream,nodeList);
		}else if(command.compare("deleteR")==0){
			isInputCorrect=rnetParser.deleteR(linestream,nodeList);
		}else if(command.compare("setV")==0){
			isInputCorrect=rnetParser.setV(linestream,nodeList);
		}else if(command.compare("unsetV")==0){
			isInputCorrect=rnetParser.unsetV(linestream,nodeList);
		}else if(command.compare("solve")==0){
			isInputCorrect=rnetParser.solve(linestream,nodeList);
		}else{
			 cout << "Error: invalid command" << endl;//invalid command
		}
		cin.clear();
		cout << "> ";//ready to receive the arguments again
		getline (cin, inputString);

	} // End input loop until EOF.

	return 0;
}
