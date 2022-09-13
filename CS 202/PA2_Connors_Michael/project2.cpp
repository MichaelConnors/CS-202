//============================================================================
// Name        : project2.cpp
// Author      : Michael Connors
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Constant Declaration
const int maxCars = 5;

//Struct that contains information about a rental car
struct RentalCar{
	int year;
	string make;
	string model;
	float price;
	bool available;
};

//Function Prototypes
RentalCar getCarInfo(ifstream&);
void sortByPrice(RentalCar[]);
void userMenu(RentalCar[]);
void mySwap(RentalCar*,RentalCar*);
size_t myStringLength(const char *str);
int myStringCompare(const char *str1,const char *str2);
char *myStringCopy(char *destination, const char *source);
char *myStringCat(char *destination,const char *source);

int main() {
	RentalCar cars[maxCars];

	userMenu(cars);

}

//Method that displays the menu while the user has not chosen to exit and completes the displayed task
void userMenu(RentalCar cars[]){
	//Variables Used in Function
	int input = 0;
	ifstream infile;
	string inputFile;
	string outputFile;
	ofstream outputStream;
	int rentalPeriod = 0;
	bool runFlag = true;
	int rentedCar;

	//Runs the while loop while the condition is true
	while(runFlag){

		//Displays Menu
	cout << "[1] Read Data from File" << endl;
	cout << "[2] Print Car Data to Terminal" << endl;
	cout << "[3] Print Car Data to File" << endl;
	cout << "[4] Sort Cars by Price (Lowest to Highest)" << endl;
	cout << "[5] Check Car Availability" << endl;
	cout << "[6] Select Rental Car" << endl;
	cout << "[7] End Program" << endl;
	cout << endl << "Please select an option: ";
	cin >> input;
	while(input < 1 || input > 7){
		cout << "Invalid Input" << endl;
		cout << "Please select an option: ";
		cin >> input;
	}
	cout << endl;

	//Switch statement to handle all possible cases
	switch(input){

	//Case 1 reads in a file name from user then populates the array of structs
	case 1:
		cout << "Enter File Name: ";
		cin >> inputFile;
		infile.open(inputFile);
		for(int i = 0;!infile.eof();i++){
				cars[i] = getCarInfo(infile);
			}
		infile.close();
		cout << endl;
		break;

		//Case 2 displays the data to the terminal
	case 2:
		for(int i = 0; i < maxCars;i++){
			cout << "[" << i << "] " << cars[i].year << " " << cars[i].make << " "
					<< cars[i].model << ", $" << cars[i].price << " per day, Available: "
					<< boolalpha << cars[i].available << endl;
		}
		cout << endl;
		break;

		//Case 3 displays the data in a different file
	case 3:
		cout << "Enter Output File Name: ";
		cin >> outputFile;
		outputStream.open(outputFile);
		for(int i = 0; i < maxCars;i++){
			outputStream << cars[i].year << " " << cars[i].make << " "
					<< cars[i].model << ", $" << cars[i].price << " per day, Available: "
					<< boolalpha << cars[i].available << endl;
		}
		outputStream.close();
		break;

		//Case 4 sorts the cars by price
	case 4:
	{
		sortByPrice(cars);
		break;
	}
		//Case 5 Displays the Cars available for rental
	case 5:
		cout << "Enter the desired amount of days: ";
		cin >> rentalPeriod;
		for(int i = 0; i < maxCars;i++){
			float totalCost = 0.0;
			if(cars[i].available == true){
				totalCost = rentalPeriod * cars[i].price;
				cout << "[" << i << "] " << cars[i].year << " " << cars[i].make << " "
						<< cars[i].model << ", Total Cost $" << totalCost << endl;
			}
		}
		cout << endl;
		break;

		//Case 6 User chooses the car to rent and the amount of days, if unavailable it will display an error prompt and asks for a different car
	case 6:
		rentedCar = 0;
		float totalCost;
		cout << "Enter the number of the car you wish to rent: ";
		cin >> rentedCar;
		while(cars[rentedCar].available == false){
			cout << "Sorry that car is currently unavailable. " << endl << endl;
			cout << "Please select another car: ";
			cin >> rentedCar;
		}
		cout << endl << "How many days do you wish to rent: ";
		cin >> rentalPeriod;
		totalCost = rentalPeriod * cars[rentedCar].price;
		cars[rentedCar].available = false;
		cout << endl << "Success! You have selected the " << cars[rentedCar].year << " " << cars[rentedCar].make
				<< " " << cars[rentedCar].model << endl;
		cout << "Your total cost is $" << totalCost << endl << endl;

		break;

		//Case 7 Sets the run condition equal to false ending the loop
 	case 7:
		cout << "Have a nice day!";
		runFlag = false;
		break;

	default:
		cout << "Not a valid Input" << endl << endl;
		break;
	}


	}
}

//Function that reads in data from desired file
RentalCar getCarInfo(ifstream &infile){
	RentalCar car;
	infile >> car.year >> car.make >> car.model >> car.price >> car.available;
	return car;
}

//Swaps the indexes of a RentalCar array
void mySwap(RentalCar *car1,RentalCar *car2){
	RentalCar tmp;
	tmp = *car2;
	*car2 = *car1;
	*car1 = tmp;
}
//Sorts the cars by price from lowest price to highest
void sortByPrice(RentalCar cars[]){
	for(int i = 0; i < maxCars;i++){
		for(int j = 0;j < maxCars;j++){
		if(cars[j].price > cars[i].price){
			mySwap(&cars[i],&cars[j]);
		}
		}
	}
}
//Returns the Length of a given string
size_t myStringLength(const char *str1){
	int stringLength;
	while(*str1 != '\0'){
		stringLength++;
		str1++;
	}
	return stringLength;
}

//Compares two strings
int myStringCompare(const char* str1, const char* str2){
	int compare = 2;
		while(*str1 == *str2 || *str1 != '\0' && *str2 != '\0'){
			compare = 0;
			str1++;
			str2++;
		}
		if(*str1 < *str2){
			compare = -1;
		}else if(*str1 > *str2){
			compare = 1;
		}
		str1++;
		str2++;
	return compare;
}

//Copies string from source to destination
char *myStringCopy(char *destination, char *source){
	for(int i = 0;*source != '\0';i++){
		destination[i] = *source;
		source++;
	}
	return destination;
}

//Combines two strings beginning at the end of destination
char *myStringCat(char *destination, const char *source){
	while(*destination != '\0'){
		destination++;
	}
	if(*destination == '\0'){
		for(int i = 0;*source != '\0';i++){
			destination[i] = source[i];
		}
	}
	return destination;
}






















