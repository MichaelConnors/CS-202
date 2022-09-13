//============================================================================
// Name        : project3.cpp
// Author      : Michael Connors
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Constants
const int MAX_SIZE = 256;
const bool NOT_AVAILABLE = false;
const int MAX_CARS = 5;
const char space = ' ';

//Declaration of Object RentalCar
class RentalCar{
public:
    RentalCar(){

    }
	RentalCar(int year, char *make,char *model,float price,bool available=NOT_AVAILABLE);

	//Member functions
	void setYear(int);
	void setMake(char *make);
	void setModel(char *model);
	void setPrice(float);
	void setAvailablility(bool);
	int getYear();
	char* getMake();
	char* getModel();
	float getPrice();
	bool getAvailability();
	void printData();
	float estimateCost(int);
private:
    //Member variables
	int m_year;
	char m_make[MAX_SIZE];
	char m_model[MAX_SIZE];
	float m_price;
	bool m_available;
};

//Declaration of RentalAgency
struct RentalAgency{
	char name[MAX_SIZE];
	int zipcode[5];
	RentalCar inventory[MAX_CARS];
};
//Global Function Declaration
void getDataFromFile(RentalAgency*);
void run();
void printAllData(RentalAgency*);
void estimateRentalCost(RentalAgency*);
void findMostExpensive(RentalAgency*);
void printAvailable(RentalAgency*);
char* myStrCopy(char*,const char*);
size_t myStrLength(const char*);
int myStrCompare(const char*,const char*);

int main() {
	run();
    return 0;
}
//Initialization of member functions
void RentalCar::setYear(int year){
	m_year = year;
}
void RentalCar::setMake(char *make){
    myStrCopy(m_make,make);
}
void RentalCar::setModel(char *model){
    myStrCopy(m_model,model);
}
void RentalCar::setPrice(float price){
	m_price = price;
}
void RentalCar::setAvailablility(bool available){
	m_available = available;
}
int RentalCar::getYear(){
	return m_year;
}
char* RentalCar::getMake(){
	return m_make;
}
char* RentalCar::getModel(){
	return m_model;
}
float RentalCar::getPrice(){
	return m_price;
}
bool RentalCar::getAvailability(){
	return m_available;
}
void RentalCar::printData(){
	cout << getYear() << " " << getMake() << " " << getModel() << " " << getPrice() <<  " " << boolalpha << getAvailability();
}
float RentalCar::estimateCost(int days){
	float cost;
	cost = m_price * days;
	return cost;
}

//Gets data from file and stores it in an array
void getDataFromFile(RentalAgency *agencies){
    //Variables
    ifstream infile;
    char input[MAX_SIZE];
	char number;
	int year;
	char make[MAX_SIZE];
	char model[MAX_SIZE];
	float price;
	bool available;


	cout << "Enter the file name: ";
    cin >> input;
        infile.open(input);
        RentalAgency *agencies_ptr = agencies;
        for(int i = 0; i < 3;i++,++agencies_ptr){
		infile >> agencies_ptr->name;
		for(int j = 0;j < 5;j++){
            infile >> number;
            *(agencies_ptr->zipcode+j) = (number - '0');
		}
		RentalCar *inv_ptr = agencies_ptr->inventory;
        for(int j = 0; j < MAX_CARS;j++,++inv_ptr){
		infile >> year >> make >> model >> price >> available;
		inv_ptr->setYear(year);
		inv_ptr->setMake(make);
		inv_ptr->setModel(model);
		inv_ptr->setPrice(price);
		inv_ptr->setAvailablility(available);

        }
        }
	}
	//Runs the program
	void run(){
	    int userChoice;
	    RentalAgency agencies[3];
        bool runFlag = true;

    while(runFlag){
	    cout << "[1] " << "Get data from file" << endl;
	    cout << "[2] " << "Print data to terminal" << endl;
	    cout << "[3] " << "Estimate Car cost" << endl;
	    cout << "[4] " << "Find most expensive car" << endl;
	    cout << "[5] " << "Print available cars to file" << endl;
	    cout << "[6] " << "Exit Program" << endl;
	    cout << "Select an option: ";
	    cin >> userChoice;
	    cout << endl;
    while(userChoice > 6){
    cout << "Invalid selection please choose again: ";
    cin >> userChoice;
    }
    //Switch to handle choices
	    switch(userChoice){
    case 1:
        getDataFromFile(agencies);
        break;
    case 2:
        printAllData(agencies);
        break;
    case 3:
        estimateRentalCost(agencies);
        break;

    case 4:
        findMostExpensive(agencies);
        break;
    case 5:
        printAvailable(agencies);
        break;
    case 6:
        runFlag = false;
        cout << "Have a nice day!" << endl;
        break;
    default:
        cout << "Something went wrong :(";
        break;

	    }
    }
	}
	//Prints the data to terminal
void printAllData(RentalAgency *agencies){

    RentalAgency *agencies_ptr = agencies;
    for(int i = 0; i < 3;i++,*(agencies_ptr++)){
        cout << agencies_ptr->name << " ";
        for(int j = 0; j < 5;j++){
            cout << *(agencies_ptr->zipcode+j);
        }
        cout << endl;

        RentalCar *inv_ptr = agencies_ptr->inventory;
        for(int j = 0;j < MAX_CARS;j++,++inv_ptr){
            cout << inv_ptr->getYear() << " ";
            cout << inv_ptr->getMake() << " ";
            cout << inv_ptr->getModel() << ", ";
            cout << inv_ptr->getPrice() << " per day, ";
            cout << "Available:" << boolalpha << inv_ptr->getAvailability() << endl;
        }
        cout << endl;
    }
    }
    //Estimates the cost of a car for an inputted number of days
void estimateRentalCost(RentalAgency *agencies){
    int agencySelect;
    int carSelect;
    int daysRented;
    float cost;

    RentalAgency *agencies_ptr = agencies;
      for(int i = 0; i < 3;i++,agencies_ptr++){
         cout << "[" << i << "] " << agencies_ptr->name << endl;
       }
        cout << "Select an agency: ";
        cin >> agencySelect;
        agencies_ptr = agencies+agencySelect;
        RentalCar *inv_ptr = agencies_ptr->inventory;
        for(int i = 0;i < MAX_CARS;i++,inv_ptr++){
            cout << "[" << i << "] " << inv_ptr->getMake() << " " << inv_ptr->getModel() << endl;
        }
            cout << "Select a car: ";
            cin >> carSelect;
            inv_ptr = agencies_ptr->inventory+carSelect;
            cout << "How many days would you like to rent: ";
            cin >> daysRented;
            cout << endl;
            cost = inv_ptr->estimateCost(daysRented);
            cout << "Your estimated cost for the " << inv_ptr->getYear() <<
             " " << inv_ptr->getMake() << " " << inv_ptr->getModel() << " is $" << fixed  << setprecision(2)<< cost  << " per day." << endl;
}
//Finds the most expensive car of all the agencies
void findMostExpensive(RentalAgency *agencies){
        RentalCar *mostExpensive;
        RentalAgency *agencies_ptr = agencies;
        RentalCar *inv_ptr = agencies_ptr->inventory;
        mostExpensive = inv_ptr;
        for(int i = 0;i < 3;i++,agencies_ptr++){
            for(int j = 0;j < MAX_CARS;j++,inv_ptr++){
                if(inv_ptr->getPrice() > mostExpensive->getPrice()){
                    mostExpensive = inv_ptr;
                }
            }
        }
        cout << "The most expensive car is: " << mostExpensive->getMake() << " " << mostExpensive->getModel() << " $" << mostExpensive->getPrice() << endl;
}
//Prints the cars available for rental
void printAvailable(RentalAgency *agencies){
    ofstream outFile;
    char outputName[MAX_SIZE];
    cout << "Enter a file name: ";
    cin >> outputName;
    outFile.open(outputName);
        RentalAgency *agencies_ptr = agencies;
    for(int i = 0; i < 3;i++,*(agencies_ptr++)){
        outFile << agencies_ptr->name << ":" << endl;
        RentalCar *inv_ptr = agencies_ptr->inventory;
        for(int j = 0;j < MAX_CARS;j++,++inv_ptr){
            if(inv_ptr->getAvailability() == true){
            outFile << inv_ptr->getYear() << " ";
            outFile << inv_ptr->getMake() << " ";
            outFile << inv_ptr->getModel() << ", ";
            outFile << inv_ptr->getPrice() << " per day. " << endl;
            }
        }
        outFile << endl;
    }
    }


//Copies the given c-string to another c-string
char* myStrCopy(char *destination,const char *source){
        while((*destination++ = *source++) != '\0');
    return destination;
}
size_t myStrLength(const char *str){
    size_t strLength;
    for(int i = 0;*str != '\0';i++,str++){
        strLength = i;
    }
    return strLength+1;
}
int myStrCompare(const char *str1,const char *str2){
    int comparison;
    while(*str1 == *str2 && *str1 != '\0' || *str2 != '\0'){
        comparison = 0;
        str1++;
        str2++;
    }
    if(*str1 > *str2){
        comparison = 1;
    }else{
    comparison = -1;
    }

}
char* myStrCat(char *destination,char *source){
    while(*destination != '\0'){
        destination++;
    }
    while(source != '\0'){
        *destination = *source;
        source++;
    }
    return destination;
}


