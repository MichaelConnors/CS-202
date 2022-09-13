#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <string.h>

const int MAX_SIZE = 256;

class Car:public Vehicle{
public:
    Car();
    Car(char*,int,float*);
    Car(Car &c1);
    ~Car();

    friend ostream& operator<<(ostream& os, const Car &c1);

    void setPlates(char*);
    void setThrottle(int);
    char* getPlates();
    int getThrottle();

    void move(float* lla);
    void drive(int);
    void operator=(const Car &c1);
private:
    char m_plates[MAX_SIZE];
    int m_throttle;
};
Car::Car(){
    m_throttle = 0;
    cout << "Car #" << m_vin << ": Default-ctor" << endl;
}
Car::Car(char* plates,int vin,float* lla):Vehicle(vin,lla){
    m_throttle = 0;
    setPlates(plates);
    cout << "Car #" << m_vin << ": Parameterized-ctor" << endl;

}
Car::Car(Car &c1):Vehicle(c1){
    setPlates(c1.m_plates);
    setThrottle(c1.m_throttle);
    cout << "Car #" << m_vin << ": Copy-ctor" << endl;
}
Car::~Car(){
    cout << "Car #" << m_vin << "Dtor" << endl;
    delete &m_plates;
    delete &m_throttle;
}
void Car::move(float* lla){
    drive(75);
    cout << "Car #" << m_vin << ": DRIVE to destination, with throttle @ 75" << endl;
    setLLA(lla);
}
ostream& operator<<(ostream& os, const Car &c1){

    os << "Car #" << c1.m_vin << " " << c1.m_plates << ", Throttle: " << c1.m_throttle;
    for(int i = 0;i < 3;i++){
        os << " " << c1.m_lla[i];
    }
    os << endl;

    return os;
}
void Car::operator=(const Car &c1){
    Vehicle::operator=(c1);
    strcpy(m_plates,c1.m_plates);
    m_throttle = c1.m_throttle;
    cout << "Car #" << m_vin << ": Assignment" << endl;

}
void Car::drive(int throttle){m_throttle = throttle;}
void Car::setPlates(char* plates){strcpy(m_plates,plates);}
void Car::setThrottle(int throttle){m_throttle = throttle;}
char* Car::getPlates(){return m_plates;}
int Car::getThrottle(){return m_throttle;}
#endif // CAR_H_INCLUDED
