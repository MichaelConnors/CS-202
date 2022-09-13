

#include "ArrayList.h"

//Helper function to resize the array to a given value
void ArrayList::resize(size_t count){

    DataType *tmp = new DataType[m_size];

if(count > m_maxsize){
    m_maxsize = count;
    for(int i = 0;i < m_size;i++){
        tmp[i] = m_array[i];
    }
    delete [] m_array;
    m_array = NULL;
    m_array = new DataType[m_maxsize];
    for(int i = 0;i < m_size;i++){
        m_array[i] = tmp[i];
    }
    if(m_maxsize > m_size){
        for(int i = m_size+1; i < m_maxsize;i++){
            m_array[i] = DataType();
            }
        }
    }else if(count < m_maxsize){
        m_maxsize = count;
        if(m_maxsize < m_size){
        m_size = 0;
        for(int i = 0;i < m_maxsize;i++){
            tmp[i] = m_array[i];
            m_size++;
        }
        }else if(m_maxsize >= m_size){

            for(int i = 0;i < m_size;i++){
                tmp[i] = m_array[i];
            }
            }else{
                std::cout << "Array is already this size." << std::endl;
            }
            delete [] m_array;
            m_array = NULL;
            m_array = new DataType[m_maxsize];
            for(int i = 0;i < m_size;i++){
                m_array[i] = tmp[i];
            }
            if(m_size < m_maxsize){
                for(int i = m_size+1;i < m_maxsize;i++){
                    m_array[i] = DataType();
                }
            }
        }
    delete [] tmp;
}
//Default ctor
ArrayList::ArrayList()
: m_maxsize(0),
m_size(0),
m_array(NULL)
{
}
//Parameterized ctor
ArrayList::ArrayList(size_t count,const DataType& value)
: m_maxsize(count)
{
    m_size = 0;
    m_array = new DataType[m_maxsize];
    for(int i = 0;i < m_maxsize;i++){
        m_array[i] = value;
        m_size++;
    }
}
//Copy ctor
ArrayList::ArrayList(const ArrayList& other)
: m_maxsize(other.m_maxsize),
m_size(other.m_size)
{
    m_array = new DataType[m_maxsize];
    for(int i = 0; i < m_size;i++){
        m_array[i] = other.m_array[i];
    }
}
//Dtor
ArrayList::~ArrayList(){
    delete m_array;
}
//Override of the assignment operator
ArrayList& ArrayList::operator=(const ArrayList& rhs){
    delete m_array;
    m_array = NULL;

    m_maxsize = rhs.m_maxsize;
    m_size = rhs.m_size;
    m_array = new DataType[m_maxsize];
    for(int i = 0;i < m_maxsize;i++){
        m_array[i] = rhs.m_array[i];
    }
    return *this;
}
//Returns a pointer to the first value in the array
DataType* ArrayList::front(){
    if(m_array == NULL){
        return NULL;
    }else{
        return m_array;
    }
}
//Returns value to the last element in the array
DataType* ArrayList::back(){
    if(m_array == NULL){
        return NULL;
    }else{
        return m_array+m_size;
    }
}
//Finds a given value and returns a pointer to the element before it
DataType* ArrayList::find(const DataType& target,DataType*& previous){
    DataType *data_ptr = NULL;
    for(int i = 0;i < m_size;i++,m_array++){
        if(target == *m_array && i == 0){
            data_ptr = m_array;
            previous = NULL;
            return data_ptr;
            break;
        }else if(target == *m_array && i > 0){
            data_ptr = m_array;
            previous = (m_array-1);
            return data_ptr;
            break;
        }
    }
    return data_ptr;
}
//Inserts a given value after a specified target
DataType* ArrayList::insertAfter(const DataType& target,const DataType &value){

    bool targetFlag = false;
    int targetPosition = 0;

    for(int i = 0; i < m_size;i++){
        if(m_array[i] == target){
            targetFlag = true;
            targetPosition = i;
            break;
        }
    }
    if(targetFlag){
    if(m_size+1 < m_maxsize){
                    m_size++;
                    for(int i = m_size;i > targetPosition;i--){
                        m_array[i+1] = m_array[i];
                    }
                    m_array[targetPosition+1] = value;
                    return (m_array+targetPosition+1);
        }else if(m_size == m_maxsize){
            resize(m_maxsize+1);
                    for(int i = m_size-1;i > targetPosition;i--){
                       m_array[i+1] = m_array[i];
                    }
                    m_size++;
                    m_array[targetPosition+1] = value;
                        return (m_array+targetPosition+1);
            }
    }else{
        return NULL;
    }
}
//Inserts a given value before a specified target
DataType* ArrayList::insertBefore(const DataType& target,const DataType& value){

    bool targetFlag = false;
    int targetPosition;

    for(int i = 0;i < m_size;i++){
        if(m_array[i] == target){
            targetFlag = true;
            targetPosition = i;
            break;
        }
    }
    if(targetFlag){
        if(m_size+1 < m_maxsize){
                m_size++;
            for(int i = m_size;i >= targetPosition;i--){
                m_array[i+1] = m_array[i];
            }
            m_array[targetPosition] = value;
            return (m_array+targetPosition);
        }else if(m_size == m_maxsize){
            resize(m_maxsize+1);
            for(int i = m_size-1;i >= targetPosition;i--){
                m_array[i+1] = m_array[i];
            }
            m_size++;
            m_array[targetPosition] = value;
            return (m_array+targetPosition);
        }

    }else{
        return NULL;
    }

}
//Erases a given element from the array
DataType* ArrayList::erase(const DataType &target){
    for(int i = 0;i < m_size;i++){
        if(m_array[i] == target){
            for(int j = i;j < m_size;++j){
                if(j != m_size-1){
                    m_array[j] = m_array[j+1];
                }else{
                    m_array[j] = DataType();
                }
            }
            m_size--;
            if(i != m_maxsize){
            return m_array+i;
            }else{
                return NULL;
            }
        }
    }
}
//Allows bracket indexing
DataType& ArrayList::operator[](size_t position){

    return m_array[position];

}
//Returns the size of valid elements in the array
size_t ArrayList::size()const{
    return m_size;
}
//Checks to see if the array is empty
bool ArrayList::empty()const{
    if(m_array == NULL){
        return true;
    }else{
        return false;
    }
}
//Clears all data within the array
void ArrayList::clear(){

    delete [] m_array;
    m_array = NULL;
    m_size = 0;
    m_maxsize = 0;

}
//Override for the operator<<
std::ostream & operator<<(std::ostream& os, const ArrayList& arrayList){
    os << "Max Size: " << arrayList.m_maxsize << " Size: " << arrayList.m_size << " Data:";
    for(int i = 0; i < arrayList.m_maxsize;i++){
        os << " " << arrayList.m_array[i];
    }
    os << std::endl;
    return os;
}
