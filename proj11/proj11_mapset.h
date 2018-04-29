/**************************************
 * File:  proj11_mapset.h
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on April 20, 2018, 8:45 PM
 **************************************/
#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;


// Struct for a Node which is made up
// of a key and value pair. Contains all 
// public vals
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  //returns ostream of formatted node
  //params are ostream and the node to print
  friend ostream& operator<<(ostream &out, const Node &n){
    // prints out an formatted node to an ostream
    out << n.first << ':' << n.second;
    return out;
  }
};

// Node constructor - creates a new node
// params are the key and value, type is
// determined by template
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
  first = key;
  second = value;
}

// returns a bool, true if calling node
// has a key value less than argument node key
// parameter is another node to compare with
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
  //checks the key values of each node
  if(first > n.first){
    return false;
  }else{
    return true;
  }
}

// returns a bool, true if calling node
// has a key value equal to argument node key
// parameter is another node to compare with
template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
  //checks if keys of two nodes are equal
  if(first == n.first){
    return true;
  }else{
    return false;
  }
}


// Struct for a MapSet, which contains both
// public and private data. Most important is the
// array of nodes, last value, and capacity
// types determined by template
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* head_ = nullptr;
  Node<K,V>* tail_ = nullptr;  
  size_t sz_ = 0;
  pair<Node<K,V>*, Node<K,V>* > find_key(K);

 public:
  MapSet()=default;
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);

  //returns an ostream with a formatted version of the mapset
  //params are the ostream and the mapset to print
  friend ostream& operator<<(ostream &out, const MapSet &ms){ 
    Node<K,V>* to_node = ms.head_;
    while (to_node != nullptr){
      out << to_node -> first << ':' << to_node -> second;
      if(to_node -> next == nullptr){
        //do nothing
        return out;
      }else{
        out << ", ";
        to_node = to_node -> next;
      }
    }
    return out;
  }  
};

// constructor for a MapSet using intitializer_list
// loops through every item in list and adds to 
// mapset array. Param is the init_list
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
  //sets the capacity of node, and creates new array
  size_t sz = il.size();
  head_ = nullptr;
  tail_ = nullptr;
  //loops through each item in the init list
  for(int i=0; i<sz; i++){
    auto item = *(il.begin() + i);
    Node<K, V> temp_node(item.first, item.second);
    add(temp_node);
  }
}

// constructor for a MapSet using another MapSet
// copies arg Map into a new MapSet
// param is the MapSet to copy
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
  //sets capacity and makes new array
  head_ = nullptr;
  tail_ = nullptr;
  sz_ = 0;
  Node<K,V>* to_node = ms.head_;
  while (to_node != nullptr){
    add(*to_node);
    to_node = to_node -> next;
  }
}

// returns a MapSet that is set to be equal to arg
// param is the MapSet that we want to convert calling to
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
  //assigns the head and tail of calling to the arg's
  //sets capacity and makes new array
  head_ = nullptr;
  tail_ = nullptr;
  sz_ = 0;
  Node<K,V>* to_node = ms.head_;
  while (to_node != nullptr){
    add(*to_node);
    to_node = to_node -> next;
  }
  return *this;
}	

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
  Node<K,V>* to_del = head_;
  while (to_del != nullptr){
	  head_ = head_->next;
	  delete to_del;
	  to_del = head_;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

// returns a size_t - number of nodes in map
// no params, just checks what sz is
template<typename K, typename V>
size_t MapSet<K,V>::size(){
  return sz_;
}

// returns a pointer pair, finds where to insert node
// param is the key to search for within linked list
template<typename K, typename V>
pair<Node<K,V>*, Node<K,V>* > MapSet<K,V>::find_key(K key){
  if(head_ == nullptr && tail_ == nullptr){
    //if the maps is completely empty
    return {nullptr,nullptr};
  }else if(head_ -> first == key){
    //if the key matches first element
    return {head_, head_};
  }
  if(key <= head_ -> first){
    //if the key should go in the front of list
    return {nullptr, head_};
  }
  //loops through the list till a location is found
  for(Node<K,V>*n = head_; n!=tail_; n=n->next){
    if(key <= n -> next -> first){
      //if key is less than or equal to item existing
      return {n, n->next};
    }
  }
  //returns if key is larger than all other keys
  return {nullptr,nullptr};
}

// returns bool. True if item successfully added
// parameter is a Node to add to the MapSet
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> nod){
  Node<K,V>* n = new Node<K,V>(nod.first,nod.second);
  auto key = n -> first;
  auto ptr_pair = find_key(key);
  
  Node<K,V>* f_pair = ptr_pair.first;
  Node<K,V>* s_pair = ptr_pair.second;
  //checks where the pointers point to
  if(s_pair == nullptr && f_pair == nullptr && sz_ == 0){
     //insert in the front of mapset - first item
     tail_ = n;
     n->next = nullptr;
     head_ = n;
     sz_ ++;
    return true;
  }else if(s_pair == nullptr && f_pair == nullptr){
    //insert at the very back of the mapset
    tail_ -> next = n;
    tail_ = n;
    sz_ ++;
    return true;
  }else if(s_pair == f_pair){ 
    //this means node is equivalent to first item
    return false;
  }else if(f_pair == nullptr){
    //insert in the front of mapset
     n->next = s_pair;
     head_ = n;
     sz_ ++;
     return true;
  }else if(f_pair->first == key || s_pair->first == key){
    //if the key already exists in the linked list
    return false;
  }else{
    //insert between the two different pointers
    n->next = s_pair;
    f_pair -> next = n;
    sz_ ++;
    return true;
  }
  return false;
}

// returns bool. True if item succesffully removed
// parameter is a key of node we want to remove
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
  //loops through to make sure if key isn't in it
  for(Node<K,V>*n = head_; n!=tail_; n=n->next){
    if (n -> first == key){
      break;
    }else if(n->next == nullptr){
      return false;
    }
  }
  //creates a temporary pointer to head
  Node<K,V>* to_del = head_;
  //checks if first node is a match
  if(to_del -> first == key){
    head_ = to_del -> next;
    delete to_del;
    return true;
  }
  //loops through every item in linked list to check
  for(Node<K,V>*n = head_; n!=tail_; n=n->next){
    //checks if the following item is the key
    if(n -> next -> first == key){
      //if match, just cut out the item in link
      n -> next = n->next -> next;
      return true;
    }
  }
  return false;
}

// returns a Node that has target key val
// param is the target key val 
// type determined by template
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
  //loops through to see if key isn't in map
  for(Node<K,V>*n = head_; n!=tail_; n=n->next){
    if (n -> first == key){
      break;
    }else if(n->next == nullptr){
      return {"",0};
    }
  }
  //gets the pointer with key
  auto ptr_pair = find_key(key);
  Node<K,V>* f_pair = ptr_pair.first;
  Node<K,V>* s_pair = ptr_pair.second;
  //makes sure that first pair isn't null
  if((f_pair != nullptr)){
    //checks if key exists in map
    if(f_pair->first == key){
      //return the pointer which is the Node with key
      return *f_pair;
    }
  }
  //makes sure the second pair isn't null
  if((s_pair != nullptr)){
    //checks if key exists in map
    if(s_pair->first == key){
      //return the pointer which is the Node with key
      return *s_pair;
    }
  }
  //default Node
  return {"",0};
}

// returns a bool, true if MapSet successfully updated
// params are a key and a val for node
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
  //gets the pointer with key
  auto ptr_pair = find_key(key);
  Node<K,V>* f_pair = ptr_pair.first;
  Node<K,V>* s_pair = ptr_pair.second;
  
  //makes sure that first pair isn't null
  if((f_pair != nullptr)){
    //checks if key exists in map
    if(f_pair->first == key){
      f_pair -> second = value;
      //return the pointer which is the Node with key
      return true;
    }
  }
  //makes sure the second pair isn't null
  if((s_pair != nullptr)){
    //checks if key exists in map
    if(s_pair->first == key){
      s_pair -> second = value;
      //return the pointer which is the Node with key
      return true;
    }
  }
  return false;
}

// returns an int, based on how two Maps compare
// param is the MapSet to compare with calling mapset
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
  Node<K,V>* temp_node = head_;
  //loops through every item in linked list to check
  for(Node<K,V>*n = ms.head_; n!=nullptr; n=n->next){
    //checks if the following item is the key
    auto arg_ = n->first;
    auto call_ = temp_node -> first;
    auto arg_next = n->next;
    auto call_next = temp_node -> next;
    if(arg_ < call_){
      return 1;
    }else if(arg_ > call_){
      return -1;
    }else if(arg_next == nullptr && call_next != nullptr){
      return 1;
    }else if(arg_next != nullptr && call_next == nullptr){
      return -1;
    }else{
      temp_node = call_next;
    }
  }
  return 0;
}

// returns a MapSet that is union of two maps
// param is MapSet to make a union relation with
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
  MapSet<string, long> ms_temp(ms);
  //loops through calling map and adds to new map
  for(Node<K,V>*n = head_; n!=nullptr; n=n->next){
    if(!ms_temp.add(*n)){
      sz_++;
      auto key = n->first;
      auto value = n->second;
      //updates with calling data (overrides)
      ms_temp.update(key,value);
    }
  }
  return ms_temp;
}

// returns a MapSet that is intersection of two maps
// param is MapSet to make intersection with
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
  MapSet new_map;
  //loops through calling map and adds to new map
  for(Node<K,V>*n = ms.head_; n!=nullptr; n=n->next){
    Node<K,V> temp_node;
    temp_node = get(n->first);
    //true if both maps have same key
    if(temp_node.first != ""){
      new_map.add(temp_node);    
    }
  }
  return new_map;
}

#endif
  
