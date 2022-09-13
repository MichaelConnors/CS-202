#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Constants
const int MAX_SIZE = 256;
const char* DFT_TYPE = "";
const int MAX_SENSORS = 3;
const int MAX_CARS = 5;
const float GPS_COST = 5.0;
const float CAMERA_COST = 10.0;
const float LIDAR_COST = 15.0;
const float RADAR_COST = 20.0;
const char BEGINNING_OF_SENSOR = '{';
const char END_OF_SENSOR = '}';
const char GPS = 'g';
const char LIDAR = 'l';
const char RADAR = 'r';
const char CAMERA = 'c';
char* myStrCopy(char*,const char*);

//Sensor class
class Sensor{
public:
    //Class prototypes
    Sensor();
    Sensor(char *type);
    Sensor(const Sensor & sensor);

    //Member Functions
    void setType(char*);
    void setExtraCost(float);

    char* getType();
    float getExtraCost();

    void resetGpsCnt();
    void resetCamCnt();
    void resetLidarCnt();
    void resetRadarCnt();

    int getGpsCnt();
    int getCamCnt();
    int getLidarCnt();
    int getRadarCnt();

    void gpsIncrement();
    void radarIncrement();
    void lidarIncrement();
    void cameraIncrement();

    bool operator==(const Sensor &s1);

private:
    //Member variables
    char m_type[MAX_SIZE];
    float m_extracost;

    static int gps_cnt;
    static int camera_cnt;
    static int lidar_cnt;
    static int radar_cnt;
};

//Initializing static variables
int Sensor::camera_cnt = 0;
int Sensor::gps_cnt = 0;
int Sensor::lidar_cnt = 0;
int Sensor::radar_cnt = 0;

//Car class
class Car{
public:
    //Class Prototypes
    Car(){m_finalprice = m_baseprice;};
    Car(char *make,char *model, int year,float baseprice,Sensor *sensor);

    //Member functions
    void setMake(char*);
    void setModel(char*);
    void setYear(int);
    void setBaseprice(float);
    void setAvailable(bool);
    void setOwner(char*);
    void updatePrice(float);

    char* getMake();
    char* getModel();
    int getYear();
    float getBaseprice();
    float getFinalprice();
    bool getAvailable();
    Sensor* getSensors();
    char* getOwner();
    void print();
    float estimateCost(int);
    Sensor* getSensorPtr();
    void getPriceWithSensor();

    void operator+(Sensor*);
    void operator+(char*);
private:
    //Member Variables
    char m_make[MAX_SIZE];
    char m_model[MAX_SIZE];
    int m_year;
    Sensor m_sensor[MAX_SENSORS];
    float m_baseprice;
    float m_finalprice;
    bool m_available;
    char m_owner[MAX_SIZE];
};
//Agency
class Agency{
public:
    //Class Prototype
    Agency(){}

    //Member Functions
    void setName(char);
    void setZipcode(int);

    char* getName();
    int getZipcode();

    void readAllData();
    void printAllData();
    void printAvailableCars();
    void findMostExpensive();
    void totalSensors();

    Car& operator[](unsigned int index);

private:
    //Member Variables
    char m_name[MAX_SIZE];
    int m_zipcode;
    Car m_inventory[MAX_CARS];
};
//Class initializations
Sensor::Sensor(){
myStrCopy(m_type,DFT_TYPE);
m_extracost = 0;
}
Sensor::Sensor(char *type){
myStrCopy(m_type,type);
m_extracost = 0;
}
Sensor::Sensor(const Sensor & sensor){
    myStrCopy(m_type,sensor.m_type);
    m_extracost = sensor.m_extracost;

}
Car::Car(char* make, char* model, int year,float baseprice,Sensor *sensor){
    myStrCopy(m_make,make);
    myStrCopy(m_model,model);
    m_year = year;
    m_baseprice = baseprice;
    Sensor *sensor_ptr = m_sensor;
    for(int i = 0;i < MAX_SENSORS;i++,sensor_ptr++,sensor++){
        *m_sensor = *sensor;
    }
    m_available = false;
    *m_owner = ' ';
}
//Function declarations
void run();
size_t myStrLength(const char*);
int myStrCompare(const char*,const char*);
int main(){

    run();
    return 0;

}
//String copy
char* myStrCopy(char *destination,const char *source){
        while((*destination++ = *source++) != '\0');
    return destination;
}
//Finds String length
size_t myStrLength(const char *str){
    size_t strLength;
    for(int i = 0;*str != '\0';i++,str++){
        strLength = i;
    }
    return strLength+1;
}
//String compare
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
//Updates final price
void Car::updatePrice(float priceIncrease){
    m_finalprice += priceIncrease;
}

//Prints Car data
void Car::print(){
    cout.precision(2);
    Sensor *sensor_ptr = this->getSensorPtr();
    cout << m_year << " " << m_make << " " << m_model << " Base: " << fixed << m_baseprice;
    if(*sensor_ptr->getType() == '{' && *(sensor_ptr->getType()+1) == '}'){
       cout << right << setw(40) << " Available: " << boolalpha << m_available << endl;
       }else{
           cout << " With ";
    for(int i = 0;i < MAX_SENSORS;i++,sensor_ptr++){
        cout << sensor_ptr->getType() << " ";
    }
    cout << ": " << fixed << m_finalprice << " Available: " << boolalpha << m_available << endl;
       }
}
//Runs the entire program
void run(){

    bool runFlag = true;
    int userChoice;
    Agency agency;

    while(runFlag){
    cout << "[1] Read data from file" << endl;
    cout << "[2] Print data to terminal" << endl;
    cout << "[3] Print total number of sensors" << endl;
    cout << "[4] Find most expensive car" << endl;
    cout << "[5] Exit program" << endl;
    cout << "Select an option: ";
    cin >> userChoice;

    switch(userChoice){
case 1:
    agency.readAllData();
    break;
case 2:
    agency.printAllData();
    break;
case 3:
    agency.totalSensors();
    break;
case 4:
    agency.findMostExpensive();
    break;
case 5:
    cout << "Have a nice day!";
    runFlag = false;
    break;

    }
    }

}
//Reads in data
void Agency::readAllData(){
    ifstream infile;
    char input[MAX_SIZE];
    int year;
    char make[MAX_SIZE];
    char model[MAX_SIZE];
    float baseprice;
    char sensorName[MAX_SIZE];
    bool available;
    char lessee[MAX_SIZE];
    int sensorLength = 0;


    cout << "Enter file name: ";
    cin >> input;

    infile.open(input);
    infile >> m_name >> m_zipcode;
    Car *inv_ptr = this->m_inventory;
    for(int i = 0;i < MAX_CARS;i++,inv_ptr++){

    infile >> year >> make >> model >> baseprice;

    inv_ptr->setYear(year);
    inv_ptr->setMake(make);
    inv_ptr->setModel(model);
    inv_ptr->setBaseprice(baseprice);
    inv_ptr->updatePrice(baseprice);

    Sensor *sensor_ptr = inv_ptr->getSensorPtr();

    for(int j = 0;j < MAX_SENSORS;j++,sensor_ptr++){
        infile >> sensorName;
        sensorLength = myStrLength(sensorName);
        sensor_ptr->setType(sensorName);
        if(*sensorName == BEGINNING_OF_SENSOR){
            if(*(sensorName+1) == GPS){
                sensor_ptr->gpsIncrement();
                inv_ptr->updatePrice(GPS_COST);
            }else if(*(sensorName+1) == CAMERA){
                sensor_ptr->cameraIncrement();
                inv_ptr->updatePrice(CAMERA_COST);
            }else if(*(sensorName+1) == LIDAR){
                sensor_ptr->lidarIncrement();
                inv_ptr->updatePrice(LIDAR_COST);
            }else if(*(sensorName+1) == RADAR){
                sensor_ptr->radarIncrement();
                inv_ptr->updatePrice(RADAR_COST);
            }
        }else{
            if(*sensorName == GPS){
                sensor_ptr->gpsIncrement();
                inv_ptr->updatePrice(GPS_COST);
            }else if(*sensorName == CAMERA){
                sensor_ptr->cameraIncrement();
                inv_ptr->updatePrice(CAMERA_COST);
            }else if(*sensorName == LIDAR){
                sensor_ptr->lidarIncrement();
                inv_ptr->updatePrice(LIDAR_COST);
            }else if(*sensorName == RADAR){
                sensor_ptr->radarIncrement();
                inv_ptr->updatePrice(RADAR_COST);
            }

        }
        if(*(sensorName+sensorLength-1) == END_OF_SENSOR){
            j = 3;
        }
}
    infile >> available;
    inv_ptr->setAvailable(available);
    if(!available){
        infile >> lessee;
        inv_ptr->setOwner(lessee);
    }
    }
}
//Prints all data
void Agency::printAllData(){
    Car *inv_ptr = this->m_inventory;
    cout << endl << m_name << " " << m_zipcode << endl;
    for(int i = 0;i < MAX_CARS;i++,inv_ptr++){
        inv_ptr->print();
    }
    cout << endl;
}
//Finds most expensive car and sets owner and availability
void Agency::findMostExpensive(){
    char userInput;
    int daysRented;
    char lesseeName[MAX_SIZE];
    Car *inv_ptr = this->m_inventory;
    Car *mostExpensive;
    mostExpensive = inv_ptr;
    for(int i = 0;i < MAX_CARS;i++,inv_ptr++){
        if(inv_ptr->getFinalprice() > mostExpensive->getFinalprice() && inv_ptr->getAvailable() == true){
            mostExpensive = inv_ptr;
        }
    }
    cout << "The most expensive available car is: " << mostExpensive->getYear() << " " << mostExpensive->getMake() << " " << mostExpensive->getModel() << endl;
    cout << "Would you like to rent this car?(Y/N): ";
    cin >> userInput;
    if(toupper(userInput) == 'Y'){
            inv_ptr = mostExpensive;
        cout << "Please enter your name: ";
        cin >> lesseeName;
                inv_ptr->setAvailable(false);
                inv_ptr->setOwner(lesseeName);
        cout << "Thank you for renting the: " << mostExpensive->getYear() << " " << mostExpensive->getMake() << " " << mostExpensive->getModel() << endl;

    }
}
//Finds the total amount of sensors
void Agency::totalSensors(){
    Sensor *sensor_ptr = this->m_inventory->getSensors();
    cout << endl << "Number of Gps: " << sensor_ptr->getGpsCnt() << endl;
    cout << "Number of Cameras: " << sensor_ptr->getCamCnt() << endl;
    cout << "Number of Lidars: " << sensor_ptr->getLidarCnt() << endl;
    cout << "Number of Radars: " << sensor_ptr->getRadarCnt() << endl << endl;
}
//Set and get methods
void Sensor::setExtraCost(float extraCost){m_extracost = extraCost;}
void Sensor::setType(char *type){myStrCopy(m_type,type);}
int Sensor::getCamCnt(){return camera_cnt;}
float Sensor::getExtraCost(){return m_extracost;}
int Sensor::getGpsCnt(){return gps_cnt;}
int Sensor::getLidarCnt(){return lidar_cnt;}
int Sensor::getRadarCnt(){return radar_cnt;}
char* Sensor::getType(){return m_type;}
void Sensor::resetCamCnt(){camera_cnt = 0;}
void Sensor::resetGpsCnt(){gps_cnt = 0;}
void Sensor::resetLidarCnt(){lidar_cnt = 0;}
void Sensor::resetRadarCnt(){radar_cnt = 0;}

void Car::setMake(char *make){myStrCopy(m_make,make);}
void Car::setModel(char *model){myStrCopy(m_model,model);}
void Car::setYear(int year){m_year = year;}
void Car::setBaseprice(float price){m_baseprice = price;}
void Car::setAvailable(bool available){m_available = available;}
void Car::setOwner(char *owner){myStrCopy(m_owner,owner);}
char* Car::getMake(){return m_make;}
char* Car::getModel(){return m_model;}
int Car::getYear(){return m_year;}
float Car::getBaseprice(){return m_baseprice;}
float Car::getFinalprice(){return m_finalprice;}
Sensor* Car::getSensors(){return m_sensor;}
char* Car::getOwner(){return m_owner;}
bool Car::getAvailable(){return m_available;}
//gets the pointer of the sensor array
Sensor* Car::getSensorPtr(){
Sensor *sensor_ptr = this->m_sensor;
return sensor_ptr;
}
//Increments the static variables by 1
void Sensor::gpsIncrement(){gps_cnt++;}
void Sensor::lidarIncrement(){lidar_cnt++;}
void Sensor::radarIncrement(){radar_cnt++;}
void Sensor::cameraIncrement(){camera_cnt++;}

//Overload of ==
bool Sensor::operator==(const Sensor &s){
    if(myStrCompare(m_type,s.m_type)==0){
        return true;
    }else{
        return false;
    }
}
//Overloads of +
void Car::operator+(Sensor *s1){
    *m_sensor = *s1;
}
void Car::operator+(char *lessee){
    *m_owner = *lessee;
}
//Overload of []
Car & Agency::operator[](unsigned int index){
    return m_inventory[index];
}
