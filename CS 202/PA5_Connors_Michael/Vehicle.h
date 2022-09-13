#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <iostream>
#include <string.h>

using namespace std;

const int LLA = 3;

class Vehicle{
public:
    Vehicle();
    Vehicle(int vin,float *lla);
    Vehicle(Vehicle &v1);
    ~Vehicle();

    void setLLA(float*);
    int getVin();
    float* getLLA();

    static int getIdgen();
    friend ostream& operator<<(ostream& os, const Vehicle &v1);
    void operator=(const Vehicle& v1);
    void move(float* lla);
protected:
    float m_lla[LLA];
    const int m_vin;
private:
    static int s_idgen;
};
    int Vehicle::s_idgen = 1;
Vehicle::Vehicle():m_vin(s_idgen){
    s_idgen++;
    cout << "Vehicle #" << m_vin << ": Default-ctor" << endl;
}
Vehicle::Vehicle(int vin, float *lla):m_vin(vin){
    setLLA(lla);
    cout << "Vehicle #" << m_vin << ": Parameterized-ctor" << endl;
}
Vehicle::Vehicle(Vehicle& v1):m_vin(v1.m_vin){
    s_idgen++;
    setLLA(v1.getLLA());
    cout << "Vehicle #" << m_vin << ": Copy-ctor" << endl;
}
Vehicle::~Vehicle(){
    cout << "Vehicle #" << m_vin << ": Dtor" << endl;
    delete &m_vin;
    delete &m_lla;
}
ostream& operator<<(ostream& os,const Vehicle& v1){
    os << "Vehicle #" << v1.m_vin << " @";
    for(int i = 0;i < LLA;i++){
        os << " " << v1.m_lla[i];
    }
    os << endl;
    return os;
}
void Vehicle::operator=(const Vehicle& v1){
    for(int i = 0;i < LLA;i++){
        m_lla[i] = v1.m_lla[i];
    }
    cout << "Vehicle #" << m_vin << ": Assignment" << endl;
}
void Vehicle::move(float* lla){
    setLLA(lla);
    cout << "Vehicle #" << m_vin << ": CANNOT MOVE - I DONT KNOW HOW" << endl;
}
int Vehicle::getIdgen(){return s_idgen;}
void Vehicle::setLLA(float* lla){
    for(int i = 0;i < LLA;i++,lla++){
        m_lla[i] = *lla;
    }
}
int Vehicle::getVin(){return m_vin;}
float* Vehicle::getLLA(){return m_lla;}
#endif // VEHICLE_H_INCLUDED
