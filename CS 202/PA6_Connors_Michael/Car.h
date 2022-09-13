#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <string.h>
#include "Vehicle.h"

const int MAX_SIZE = 256;

class Car:public Vehicle{
public:
    Car();
    Car(float*);
    Car(Car &c1);
    virtual ~Car();

    void setThrottle(int);
    int getThrottle();

    void move(float* lla)override;

    void drive(int);
    void operator=(const Car &c1);
private:
    int m_throttle;
    void serialize(std::ostream&)const;
};
Car::Car(){
    m_throttle = 0;
    std::cout << "Car: Default-ctor" << std::endl;
}
Car::Car(float* lla):Vehicle(lla){
    m_throttle = 0;
    std::cout << "Car: Parameterized-ctor" << std::endl;

}
Car::Car(Car &c1):Vehicle(c1){
    setThrottle(c1.m_throttle);
    std::cout << "Car: Copy-ctor" << std::endl;
}
Car::~Car(){
    std::cout << "Car: Dtor" << std::endl;
}
void Car::move(float* lla){
    drive(75);
    std::cout << "Car: DRIVE to destination, with throttle @ 75" << std::endl;
    setLLA(lla);
}
void Car::operator=(const Car &c1){
    Vehicle::operator=(c1);
    m_throttle = c1.m_throttle;
    std::cout << "Car: Assignment" << std::endl;

}
void Car::serialize(ostream& os)const{
    os << "Car: Throttle: " << m_throttle << " @";
    for(int i = 0;i < LLA;i++){
        os << " " << m_lla[i];
    }
    os << std::endl;
}
void Car::drive(int throttle){m_throttle = throttle;}
void Car::setThrottle(int throttle){m_throttle = throttle;}
int Car::getThrottle(){return m_throttle;}
#endif // CAR_H_INCLUDED
