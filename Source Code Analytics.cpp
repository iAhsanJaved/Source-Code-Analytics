#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void printSourceCode(string fileName);
int getNumberOfLines(string fileName);
int getNumberOfStatements(string fileName);
int getNumberOfTimesFORLoopExecute(string fileName);

int main() {
	string fileName;
	cout << "---------------------------------------------\n";
	cout << "|        Source Code Analytics              |";
	cout << "\n---------------------------------------------\n";
	cout << "\nEnter the name of a file: ";
	getline(cin, fileName);
	cout << endl << endl;
	printSourceCode(fileName);

	cout << "\n---------------------------------------------\n";
	cout << "Number of Lines: " << getNumberOfLines(fileName) << endl;
	cout << "Number of Statements: " << getNumberOfStatements(fileName) << endl;
	cout << "ForLoop Execute: " << getNumberOfTimesFORLoopExecute(fileName) << " times";
	cout << "\n---------------------------------------------\n";
	
	
	cout << endl;
	system("PAUSE");
	return 0;
}

void printSourceCode(string fileName){
	char tempChar;
	fstream file;
	file.open(fileName, ios::in);
	while (!file.eof()){
		tempChar = NULL;
		file.get(tempChar);
		cout << tempChar;
	}
	file.close();
	return;
}

int getNumberOfLines(string fileName){
	char tempChar;
	int numberOfLines = 0;
	fstream file;
	file.open(fileName, ios::in);
	while (!file.eof()) {
		tempChar = NULL;
		file.get(tempChar);
		if (tempChar == '\n') {
			numberOfLines++;
		}
	}
	file.close();
	return numberOfLines+1;
}

int getNumberOfStatements(string fileName) {
	char tempChar;
	int numberOfStatements = 0;
	fstream file;
	file.open(fileName, ios::in);
	while (!file.eof()) {
		tempChar = NULL;
		file.get(tempChar);
		if (tempChar == '>' || tempChar == ';') {
			numberOfStatements++;
		}
	}
	file.close();
	return numberOfStatements;
}

int getNumberOfTimesFORLoopExecute(string fileName)
{
	char tempChar;
	string tempString;
	int initialValue=0;
	string condition = "";
	int conditionRHSvalue = 0;
	string iterator = "";
	int byValue = 0;
	bool initializerFlag = false;
	bool conditionFlag = false;
	bool iteratorFlag = false;
	int forLoopExecutionCounter = 0;
	fstream file;
	file.open(fileName, ios::in);
	while (!file.eof()) {
		tempChar = NULL;
		tempString = "";
		file >> tempString;	// Read string (This statement will ignore a whilespace)
		if (initializerFlag) {
			int i = 0;
			bool flag = false;
			string tempNum="";
			while (tempString[i] != NULL){
				if (flag) {
					if (tempString[i] == ';') {
						initialValue= std::stoi(tempNum);
						flag = false;
						conditionFlag = true;
					}
					else {
						tempNum.push_back(tempString[i]);
					}
				}
				if (tempString[i] == '=') {
					flag = true;
				}
				i++;
			}
			initializerFlag = false;
		}
		else if (conditionFlag) {
			int i = 0;
			bool flag = false;
			string coditionValue = "";

			while (tempString[i] != NULL) {
				if (flag) {
					if (tempString[i] == ';') {
						conditionRHSvalue = std::stoi(coditionValue);
						flag = false;
						iteratorFlag = true;
					}
					else if (tempString[i] == '=') {
						condition.push_back(tempString[i]);
					}
					else {
						coditionValue.push_back(tempString[i]);
					}
				}
				else if (tempString[i] == '>' || tempString[i] == '=' || tempString[i] == '<' || tempString[i] == '!') {
					condition.push_back(tempString[i]);
					flag = true;
				}
				i++;
			}
			conditionFlag = false;
		}
		else if (iteratorFlag) {
			int i = 0;
			bool flag = false;
			string byValueStr = "0";
			while (tempString[i] != NULL) {
				if (flag) {
					if (tempString[i] == ')') {
						byValue = std::stoi(byValueStr);
						flag = false;
					}
					else if (tempString[i] == '+' || tempString[i] == '-' || tempString[i] == '=') {
						iterator.push_back(tempString[i]);
					}
					else {
						byValueStr.push_back(tempString[i]);
					}
				}
				else if (tempString[i] == '+' || tempString[i] == '-' || tempString[i] == '=' || tempString[i] == '!') {
					iterator.push_back(tempString[i]);
					flag = true;
				}
				i++;
			}
			iteratorFlag = false;
		}
		if (tempString == "for(" || tempString == "for(int" || tempString == "for( int") {
			initializerFlag = true;
		}
		
	}
	file.close();

	if (condition == "==" && iterator == "++") {
		for (int j = initialValue; j == conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "!=" && iterator == "++") {
		for (int j = initialValue; j != conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<" && iterator == "++") {
		for (int j = initialValue; j < conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">" && iterator == "++") {
		for (int j = initialValue; j > conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">=" && iterator == "++") {
		for (int j = initialValue; j >= conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<=" && iterator == "++") {
		for (int j = initialValue; j <= conditionRHSvalue; j++) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "==" && iterator == "--") {
		for (int j = initialValue; j == conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "!=" && iterator == "--") {
		for (int j = initialValue; j != conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<" && iterator == "--") {
		for (int j = initialValue; j < conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">" && iterator == "--") {
		for (int j = initialValue; j > conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">=" && iterator == "--") {
		for (int j = initialValue; j >= conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<=" && iterator == "--") {
		for (int j = initialValue; j <= conditionRHSvalue; j--) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "==" && iterator == "+=") {
		for (int j = initialValue; j == conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "!=" && iterator == "+=") {
		for (int j = initialValue; j != conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<" && iterator == "+=") {
		for (int j = initialValue; j < conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">" && iterator == "+=") {
		for (int j = initialValue; j > conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">=" && iterator == "+=") {
		for (int j = initialValue; j >= conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<=" && iterator == "+=") {
		for (int j = initialValue; j <= conditionRHSvalue; j += byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "==" && iterator == "-=") {
		for (int j = initialValue; j == conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "!=" && iterator == "-=") {
		for (int j = initialValue; j != conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<" && iterator == "-=") {
		for (int j = initialValue; j < conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">" && iterator == "-=") {
		for (int j = initialValue; j > conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == ">=" && iterator == "-=") {
		for (int j = initialValue; j >= conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	else if (condition == "<=" && iterator == "-=") {
		for (int j = initialValue; j <= conditionRHSvalue; j -= byValue) {
			forLoopExecutionCounter++;
		}
	}
	
	return forLoopExecutionCounter;
}
