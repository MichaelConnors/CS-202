//============================================================================
// Name        : Project1.cpp
// Author      : Michael Connors
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Constants
const int maxNames = 10;
const int maxLetters = 8;

//Funtion Prototypes
void myStringCopy(char[],const char[]);
int myStringLength(const char[]);
int myStringCompare(const char[], const char[]);
void output(char[][maxLetters],char[][maxLetters]);
void lengthSort(char[][maxLetters]);
void alphaSort(char[][maxLetters]);
void outputFile(char[][maxLetters],char[][maxLetters],string);

int main(){
	//Declaring Variables
	char names[maxNames][maxLetters];
	char copyArray[maxNames][maxLetters];
	string inputName;
	ifstream infile;

	//Prompts user for File Name
	cout << "Please enter the file name: ";
	cin >> inputName;

	//Opens file and populates Array
	infile.open(inputName);
	for(int i = 0; i < maxNames; i++){
				infile >> names[i];
				for(int j = 0;j < maxLetters;j++){
				 copyArray[i][j] = names[i][j];
				}
			}

	//Output
	cout << "Unsorted Data (Original Input Order and Name)" << endl
			<< "=============================" << endl;
	output(names,copyArray);
	lengthSort(copyArray);
	cout << "Sorted-by-Length Data" << endl
					<< "=============================" << endl;
	output(names,copyArray);
	outputFile(names,copyArray,"SortedByLength.txt");
	alphaSort(copyArray);
	cout << "Alphabetically Sorted Data" << endl
				<< "=============================" << endl;
	output(names,copyArray);
	outputFile(names,copyArray,"SortedNames.txt");



	}

	//Function to output data
void output(char names[][maxLetters],char copyArray[][maxLetters]){
	for(int i = 0;i < maxNames;i++){
		for(int j = 0;j < maxNames;j++){
			if(myStringCompare(names[j],copyArray[i]) == 0){
				cout << j << " " << copyArray[i] << endl;
				break;
			}
		}

		}
	cout << endl;
		}

	//Copy String function

void myStringCopy(char destination[],const char source[]){
		for(int i = 0;i<maxLetters;i++){
			destination[i] = source[i];
			if(destination[i] == '\0'){
				break;
			}
			}
	}

	//Finds the Length of the String
int myStringLength(const char names[]){
	int strLength = 0;
	for(int i = 0;i < maxLetters;i++){
		while(names[i] != '\0'){
			strLength++;
			i++;
		}
	}
	return strLength - 1 ;
}
	//Compares two Strings
int myStringCompare(const char arr1[],const char arr2[]){
	int compare=0;
			for(int i = 0;arr1[i] != '\0' || arr2[i] != '\0';i++){
				if(arr1[i] > arr2[i]){
					compare = 1;
						}else if(arr1[i] < arr2[i]){
							compare = -1;
					}else{
						compare = 0;
				}
			}
	return compare;
	}

//Sorts array Alphabetically
void alphaSort(char sortArray[][maxLetters]){
	char tmp[maxLetters];
	for(int i = 0;i < maxNames;i++){
		for(int j = 0;j<maxNames;j++){
			if(sortArray[i][0] < sortArray[j][0]){
				myStringCopy(tmp,sortArray[j]);
				fill(&sortArray[j][0],&sortArray[j][maxLetters],' ');
				myStringCopy(sortArray[j],sortArray[i]);
				fill(&sortArray[i][0],&sortArray[i][maxLetters],' ');
				myStringCopy(sortArray[i],tmp);
			}
		}

		}
	}

	//Sorts the Array by length
void lengthSort(char sortArray[][maxLetters]){
	char tmp[maxLetters];
	for(int i = 0;i<maxNames;i++){
		for(int j = 0;j<maxNames;j++){
			if(myStringLength(sortArray[i]) < myStringLength(sortArray[j])){
				myStringCopy(tmp,sortArray[j]);
				fill(&sortArray[j][0],&sortArray[j][maxLetters],'\0');
				myStringCopy(sortArray[j],sortArray[i]);
				fill(&sortArray[i][0],&sortArray[i][maxLetters],'\0');
				myStringCopy(sortArray[i],tmp);
			}
		}
	}
}
	//Outputs data to file
void outputFile(char names[][maxLetters],char copyArray[][maxLetters],string fileName){
	ofstream outputStream;
	outputStream.open(fileName);
	for(int i = 0;i < maxNames;i++){
			for(int j = 0;j < maxNames;j++){
				if(myStringCompare(names[j],copyArray[i]) == 0){
					outputStream << j << " " << copyArray[i] << endl;
					break;
				}
			}
			}
		cout << endl;
		outputStream.close();
			}











