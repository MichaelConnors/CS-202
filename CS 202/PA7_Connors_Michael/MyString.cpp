#include "MyString.h"

#include <iostream>
#include <cstring>


void MyString::buffer_deallocate(){
    if(m_buffer != NULL){
    delete [] m_buffer;
    }
}
void MyString::buffer_allocate(size_t size){
    if(m_buffer != NULL){
        buffer_deallocate();
    }
    m_size = size;
    m_buffer = new char[m_size];

}
MyString::MyString(){
    m_size = 0;
    m_buffer = NULL;
}
MyString::MyString(const char *str){
    m_buffer = NULL;
    m_size = strlen(str);
    buffer_allocate(m_size);
    strcpy(m_buffer,str);

}
MyString::MyString(const MyString &other){
    m_buffer = NULL;
    m_size = other.m_size;
    buffer_allocate(m_size);
    strcpy(m_buffer,other.m_buffer);
}

size_t MyString::size()const{
    return m_size;
}
size_t MyString::length(){
    return strlen(m_buffer)-1;
}
const char* MyString::c_str() const {
    char *str = NULL;

        str = new char[m_size];
        for(size_t i = 0; i < m_size;i++){
            str[i] = *(m_buffer+i);
        }
        return str;
        delete [] str;
        str = NULL;

}
bool MyString::operator==(const MyString & other)const{
    if(strcmp(m_buffer,other.m_buffer) == 0){
        return true;
    }else if (strcmp(m_buffer,other.m_buffer) != 0){
        return false;
    }
}
MyString & MyString::operator=(const MyString & str1){
    buffer_deallocate();
    m_buffer = new char[str1.m_size];
    strcpy(m_buffer,str1.m_buffer);

}
MyString MyString::operator+(const MyString & other_myStr)const{
    MyString myStr(strcat(m_buffer,other_myStr.m_buffer));
    return myStr;

}
char& MyString::operator[](size_t index){
    size_t counter = 0;
    while(counter != index){
        counter++;
    }
    return m_buffer[counter];
}
const char& MyString::operator[](size_t index)const{
    size_t counter = 0;
    while(counter != index){
        counter++;
    }
    return m_buffer[counter];
}
std::ostream& operator<<(std::ostream& os, const MyString& myStr){
    os << myStr.m_buffer << std::endl;
}

MyString::~MyString(){
    m_size = 0;
    delete [] m_buffer;
}
