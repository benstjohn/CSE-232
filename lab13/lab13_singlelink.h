#ifndef SINGLELINK_H
#define SINGLELINK_H

#include<iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
using std::ostream; using std::cout; using std::endl;
using std::ostringstream; using std::out_of_range;
using std::swap;
template <typename T>
struct Node{
public:
    Node *next_;
    T data_;
    
Node() : data_( T() ), next_(nullptr) {};
Node(T d) : data_(d), next_(nullptr) {};
};

template <typename T>
class SingleLink{
private:
    Node<T> *head_ = nullptr;
    Node<T> *tail_ = nullptr;
  
public:
  SingleLink() = default;         
  SingleLink(T dat);    
  void append_back(T);
  friend ostream& operator<<(ostream &out, SingleLink<T>& s){
    ostringstream oss;
    Node<T> *ptr;
    for(ptr = s.head_; ptr != nullptr; ptr = ptr->next_){
      oss << ptr -> data_ << ", ";
    }
    std::string link_str = oss.str();
    out << link_str.substr(0,link_str.size()-2);
    return out;
  };

  bool del(T val);
  Node<T>& operator[](size_t index){
    int count = 0;
    if(index < 0){
        throw out_of_range("whoops");
    }else{
        Node<T> *result = nullptr;
        for(Node<T> *n = head_; n != nullptr; n = n->next_){
        if (index == count){
          return *n;
        }
        count++; // of if
        } // of for
        throw out_of_range("whoops");
        return *result;
    }
  }
  
  // Rule of three stuff, if you get time. Look at 21.2
  ~SingleLink();
  SingleLink(const SingleLink &);
  SingleLink& operator=(SingleLink);
  
};

template<typename T>
SingleLink<T>::SingleLink(T dat){
  Node<T>* new_node = new Node<T>(dat);
  head_ = new_node;
  tail_ = new_node;
}

template <typename T>
void SingleLink<T>::append_back(T dat){
 Node<T>* new_node = new Node<T>(dat);
 if(tail_ != nullptr){
     tail_ -> next_ = new_node;
     tail_ = new_node;
 }else{
     head_ = new_node;
     tail_ = new_node;
 }
}

template <typename T>
SingleLink<T>::~SingleLink(){
    Node<T>* to_del = head_;
    while (to_del != nullptr){
	  head_ = head_->next_;
	  delete to_del;
	  to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

template <typename T>
SingleLink<T>& SingleLink<T>::operator=(SingleLink sl){
    swap(head_, sl.head_);
    swap(tail_, sl.tail_);
    return *this;
}

template<typename T>
SingleLink<T>::SingleLink(const SingleLink &sl){
  if (sl.head_ == nullptr){
	head_ = nullptr;
	tail_ = nullptr;
    }
    else{
	head_ = new Node<T>(sl.head_->data_);
	tail_ = head_;
	Node<T>* sl_ptr = sl.head_->next_;
	Node<T>* new_node;
	while (sl_ptr != nullptr){
	    new_node = new Node<T>(sl_ptr->data_);
	    tail_->next_ = new_node;
	    sl_ptr = sl_ptr->next_;
	    tail_ = new_node;
	}
    }
}



template<typename T>
bool SingleLink<T>::del(T val){
    Node<T>* to_del = head_;
    if(to_del -> data_ == val){
        head_ = to_del -> next_;
        delete to_del;
        return true;
    }
    for(Node<T>*n = head_; n!=tail_; n=n->next_){
      if(n -> next_ -> data_ == val){
        n -> next_ = n->next_ -> next_;
        return true;
      }
    }
    return false;
}


// YOUR STUFF HERE



#endif
  
