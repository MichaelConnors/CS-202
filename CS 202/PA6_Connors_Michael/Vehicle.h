#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <iostream>
#include <string.h>

using namespace std;

const int LLA = 3;

class Vehicle{
public:
    Vehicle();
    Vehicle(float *lla);
    Vehicle(Vehicle &v1);
    virtual ~Vehicle();

    void setLLA(float*);
    float* getLLA();

    virtual void move(float*) = 0;

    friend ostream& operator<<(ostream& os, const Vehicle &v1);
    void operator=(const Vehicle& v1);
protected:
    float m_lla[LLA];
private:
    virtual void serialize(ostream&)const;
};

Vehicle::Vehicle(){
    cout << "Vehicle: Default-ctor" << endl;
}
Vehicle::Vehicle(float *lla){
    setLLA(lla);
    cout << "Vehicle: Parameterized-ctor" << endl;
}
Vehicle::Vehicle(Vehicle& v1){
    setLLA(v1.getLLA());
    cout << "Vehicle: Copy-ctor" << endl;
}
Vehicle::~Vehicle(){
    cout << "Vehicle: Dtor" << endl;
}
ostream& operator<<(ostream& os,const Vehicle& v1){
    v1.serialize(os);
    return os;
}
void Vehicle::operator=(const Vehicle& v1){
    for(int i = 0;i < LLA;i++){
        m_lla[i] = v1.m_lla[i];
    }
    cout << "Vehicle: Assignment" << endl;
}
void Vehicle::move(float* lla){
    setLLA(lla);
}
void Vehicle::setLLA(float* lla){
    for(int i = 0;i < LLA;i++,lla++){
        m_lla[i] = *lla;
    }
}
void Vehicle::serialize(ostream& os)const{
    os << "Vehicle @";
    for(int i = 0;i < LLA;i++){
        os << " " << m_lla[i];
    }
    os << endl;
}
float* Vehicle::getLLA(){return m_lla;}
#endif // VEHICLE_H_INCLUDED
