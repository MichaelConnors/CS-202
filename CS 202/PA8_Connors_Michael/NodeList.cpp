

#include "NodeList.h"

//Default ctor
NodeList::NodeList():m_head(NULL){}

//Parameterized ctor
NodeList::NodeList(size_t count,const DataType& value){
    m_head = new Node(value);
    Node *next_ptr = m_head;
    for(int i = 0; i < count-1;i++){
        next_ptr->m_next = new Node(value);
        next_ptr = next_ptr->m_next;
    }
}
//Copy ctor
NodeList::NodeList(const NodeList& other){
    m_head = new Node(other.m_head->data(),other.m_head);
    Node *next_ptr = m_head;
    for(Node* curr = other.m_head->m_next;curr != NULL;curr = curr->m_next){
        next_ptr->m_next = new Node(curr->data(),curr->m_next);
        next_ptr = next_ptr->m_next;
    }

}
//Dtor
NodeList::~NodeList(){
    m_head = m_head->m_next;
    for(Node* curr = m_head;m_head != NULL;){
        m_head = m_head->m_next;
        delete curr;
        curr = m_head;
    }
    delete m_head;
}
//Assignment operator override
NodeList& NodeList::operator=(const NodeList& rhs){

    m_head = m_head->m_next;
    for(Node* curr = m_head;m_head != NULL;){
        m_head = m_head->m_next;
        delete curr;
        curr = m_head;
    }
    delete m_head;
    m_head = NULL;

    m_head = new Node(rhs.m_head->data(),rhs.m_head);
    Node *next_ptr = m_head;
    for(Node* curr = rhs.m_head->m_next;curr != NULL;curr = curr->m_next){
        next_ptr->m_next = new Node(curr->data(),curr->m_next);
        next_ptr = next_ptr->m_next;
    }

}
//Function to return a pointer to the first element
Node* NodeList::front(){
    if(m_head){
        return m_head;
    }else{
        return NULL;
    }
}
//Function that returns a pointer to the last element
Node* NodeList::back(){

    if(m_head){
        Node *tmp_ptr = m_head->m_next;
        for(Node* curr = m_head;curr != NULL;curr = curr->m_next,tmp_ptr = tmp_ptr->m_next){

            if(tmp_ptr == NULL){
                return curr;
            }

        }
        }else{
            return NULL;
    }

}
//Function to find a desired value and returns a pointer to the value before it
Node* NodeList::find(const DataType& target,Node*& previous){
        Node *tmp_ptr = m_head;
        for(Node* curr = m_head;curr != NULL;curr = curr->m_next){
            if(curr->data() == target && curr != m_head){
                return tmp_ptr;
                break;
            }else if(curr->data() == target && curr == m_head){
                return NULL;
            }
            tmp_ptr = tmp_ptr->m_next;
        }
        return NULL;
}
//Inserts a desired value after the specified value
Node* NodeList::insertAfter(const DataType& target,const DataType& value){
    for(Node* curr = m_head;curr != NULL;curr = curr->m_next){
        if(curr->data() == target){
                Node *tmp_ptr = new Node(value,curr->m_next);
                curr->m_next = tmp_ptr;
                return tmp_ptr;
                break;
        }
    }

}
//Inserts desired value before given value
Node* NodeList::insertBefore(const DataType& target,const DataType& value){

    Node* tmp_ptr = m_head->m_next;
    for(Node* curr = m_head;curr != NULL; curr = curr->m_next){
    if(curr->data() == target && curr == m_head){
        Node* new_ptr = new Node(value,curr);
        m_head = new_ptr;
        break;
        }else if(tmp_ptr->data() == target){
            Node* new_ptr = new Node(value,tmp_ptr);
            curr->m_next = new_ptr;
            break;
        }
        tmp_ptr = tmp_ptr->m_next;
    }

}
//Erases an element from the list
Node* NodeList::erase(const DataType& target){

    for(Node* curr = m_head;curr != NULL;curr = curr->m_next){

        if(curr->m_next && curr->m_next->m_data == target){
            Node* delNode_ptr = curr->m_next;
            curr->m_next = delNode_ptr->m_next;
            delete delNode_ptr;
            return curr->m_next;
            break;
        }

    }

}
//Allows bracket indexing of Linked list
DataType& NodeList::operator[](size_t position){
    Node* tmp_ptr = m_head;
    for(int i = 0;i != position;i++){
        tmp_ptr = tmp_ptr->m_next;
    }
    return tmp_ptr->data();
}
const DataType& NodeList::operator[](size_t position)const{
    Node* tmp_ptr = m_head;
    for(int i = 0;i != position;i++){
        tmp_ptr = tmp_ptr->m_next;
    }
    return tmp_ptr->data();
}
//Returns the size of the Linked List
size_t NodeList::size()const{
    size_t count = 0;
    for(Node* curr = m_head;curr != NULL; curr = curr->m_next){
        count++;
    }
    return count;
}
//Tests whether the list is empty or not
bool NodeList::empty()const{

    if(m_head == NULL){
        return true;
    }else{
        return false;
    }

}
//Clears the entire Linked list
void NodeList::clear(){

    m_head = m_head->m_next;
    for(Node* curr = m_head;m_head != NULL;){
        m_head = m_head->m_next;
        delete curr;
        curr = m_head;
    }
    delete m_head;

}
//Override of operator<<
std::ostream& operator<<(std::ostream& os,const NodeList& nodeList){
        os << "Node List Data:";
        for(Node* curr = nodeList.m_head; curr != NULL; curr = curr->m_next){
            os << " " << curr->data();
        }
        os << std::endl;
        return os;
}
