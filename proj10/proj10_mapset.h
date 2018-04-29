/**************************************
 * File:  proj10_mapset.h
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on April 13, 2018, 8:45 PM
 **************************************/
#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound;
#include<sstream>
using std::ostringstream; using std::copy;
using std::swap; using std::lower_bound;


// Struct for a Node which is made up
// of a key and value pair. Contains all 
// public vals
template<typename K, typename V>
struct Node {
  K first;
  V second;
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
  Node<K,V>* ary_;
  size_t last_ = 0;
  size_t capacity_ = 1;
  Node<K,V>* find_key(K);
  void grow ();
 public:
  MapSet(int sz = 2);
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
    //loops through every node in the mapset array
    for(int i=0; i < ms.last_; i++){
      //checks if the node is empty
      if(ms.ary_[i].first == ""){
        //do nothing
      }else{
        out << ms.ary_[i].first << ':' << ms.ary_[i].second;
        //adds the comma and space to each except last
        if(i != ms.last_ - 1 && ms.ary_[i+1].first != ""){
          out << ", ";
        }
      }
    }
    return out;
  }  
};

// constructor for a MapSet with only capacity
// param is the capacity to set mapset to
template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity){
  capacity_ = capacity;
  ary_ = new Node<K,V>[capacity];
  last_ = 0;
}

// constructor for a MapSet using intitializer_list
// loops through every item in list and adds to 
// mapset array. Param is the init_list
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
  //sets the capacity of node, and creates new array
  size_t sz = il.size();
  ary_ = new Node<K,V>[sz];
  capacity_ = sz;
  //loops through each item in the init list
  for(int i=0; i<il.size(); i++){
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
  size_t sz = ms.last_;
  ary_ = new Node<K,V>[sz];
  last_ = ms.last_;
  capacity_ = sz;
  //copies the arg to the new
  copy(ms.ary_, ms.ary_ + capacity_, ary_);
}

// returns a new MapSet which is copy of arg
// param is a MapSet to override calling MapSet
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){
  //swaps the values of calling and arg
  swap(ary_, ms.ary_);
  return *this;
}

// destructor for a MapSet using ~
// will delete the array to prevent leaks
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
 delete [] ary_;
}

// returns a size_t - number of nodes in map
// no params, just checks what last_ is
template<typename K, typename V>
size_t MapSet<K,V>::size(){
  return last_;
}

// returns void. Grows the MapSet to be able
// to hold all nodes added to it.
template<typename K, typename V>
void MapSet<K,V>::grow(){
  //creates new array with double the capacity
  Node<K,V>* node_arr = new Node<K,V>[capacity_ * 2];
  copy(ary_, ary_ + capacity_, node_arr);
  capacity_ = capacity_ * 2;
  swap(node_arr, ary_);
  //preventing memory leaks
  delete [] node_arr;
}

// returns a pointer to a Node, using lower_bound
// param is the key to search for within array
template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
  Node<K,V> * ptr_node;
  //lower_bound using lambda function
  ptr_node = lower_bound(ary_, ary_ + last_, key,
  [](Node<K,V> lhs, K key) { return lhs.first < key; });
  return ptr_node;
}

// returns bool. True if item successfully added
// parameter is a Node to add to the MapSet
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
  //checks if MapSet needs to grow
  if(last_ == capacity_){
    grow();
  }
  string str_key = n.first;
  //checks if the array is empty.
  if(ary_[0].first == ""){
    //if empty, add first node directly
    ary_[0] = n;
    last_++;
  }else{
    Node<K,V>* temp_ary = new Node<K,V>[capacity_]; 
    auto ptr = find_key(str_key);
    int ary_in = 0;
    //checks if pointer is end of array
    if(ptr == ary_ + last_){
      ary_in = last_;
    }else if(ptr -> first == str_key){
      //if key already exists in map
      return false;
    }else{
      //loops through array to find index of ptr
      for(int i=0; i<capacity_; i++){
        //once pointer is equal to item in array
        if(ptr -> first == ary_[i].first){
          ary_in = i;
          break;
        }
      }
    }
    last_++;
  
    //making array copy
    //up to insert
    for(int i=0; i < ary_in; i++){
      temp_ary[i] = ary_[i];
    }
    //new element
    temp_ary[ary_in] = n;
  
    //old array after insert
    for(int i=(ary_in + 1); i<capacity_; i++){
      temp_ary[i] = ary_[i-1];
    }
    //copies temp array into the actual array
    copy(temp_ary, temp_ary + capacity_, ary_);
    //prevents memory leaks
    delete [] temp_ary;
  }
 return true;
}

// returns bool. True if item succesffully removed
// parameter is a key of node we want to remove
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
  Node<K,V>* temp_ary = new Node<K,V>[capacity_]; 
  int ary_in = 0;
  //loops through array and checks for node with key
  for(int i=0; i <= last_; i++){
    //if there is a node with the target key value
    if(ary_[i].first == key){
      ary_in = i;
      break;
    }
    //if at end of loop and haven't found a match
    if(i==last_){
      return false;
    }
  }
  //making array copy
  //up to insert
  for(int i=0; i < ary_in; i++){
    temp_ary[i] = ary_[i];
  }
  //old array after insert
  for(int i=(ary_in); i<last_-1; i++){
    if(ary_[i+1].first != ""){
      temp_ary[i] = ary_[i+1];
    }
  }
  
  //copies temp array into final array
  copy(temp_ary, temp_ary + capacity_, ary_);
  //prevents memory leaks
  delete [] temp_ary;
  return true;
}

// returns a Node that has target key val
// param is the target key val 
// type determined by template
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
  auto ptr = find_key(key);
  //checks if key exists in map
  if(ptr -> first == key){
    //return the pointer which is the Node with key
    return *ptr;
  }else{
    //default Node
    return {"",0};
  }
}

// returns a bool, true if MapSet successfully updated
// params are a key and a val for node
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
  auto ptr = find_key(key);
  //checks if Node in map has matching key
  if(ptr -> first == key){
    //loops through array to find index of match
    for(int i=0; i<capacity_; i++){
      //once the match is found
      if(ptr -> first == ary_[i].first){
        //updates the array with new Node vals
        ary_[i] = {key, value};
        return true;
      }
    }
    //should never happen, but I was getting warning
    return false;
  }else{
    return false;
  }
}

// returns an int, based on how two Maps compare
// param is the MapSet to compare with calling mapset
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
  long smallest = size();
  //determines which map is smallest
  if(ms.size() < size()){
    smallest = ms.size();
  }

  //loops through smallest map
  for(int i=0; i < smallest; i++){
    string arg_str = ms.ary_[i].first;
    string call_str = ary_[i].first;
    //compares strings in pairs
    if(arg_str > call_str){
      return -1;
    }else if(call_str > arg_str){
      return 1;
    }
  }
  //if arg map is larger than calling
  if(ms.size() < size()){
    return 1;
  }else if(ms.size() > size()){
    return -1;
  }
  return 0;
}

// returns a MapSet that is union of two maps
// param is MapSet to make a union relation with
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
   MapSet<string, long> ms_temp(ms);
  //loops through calling map and adds to new map
  for(int i=0; i < size(); i++){
    string call_str = ary_[i].first;
    long call_val = ary_[i].second;
    //if the pair in calling map already in new map
    if(!ms_temp.add({call_str, call_val})){
      //updates with calling data (overrides)
      ms_temp.update(call_str,call_val);
    }
  }
  return ms_temp;
}

// returns a MapSet that is intersection of two maps
// param is MapSet to make intersection with
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
  MapSet new_map;
  long smallest = size();
  //looks to find the smallest map for loop
  if(ms.size() < size()){
    smallest = ms.size();
  }
  //loops through maps and finds which pairs match
  for(int i=0; i < smallest; i++){
    string arg_str = ms.ary_[i].first;
    Node<K,V> temp_node;
    temp_node = get(arg_str);
    //true if both maps have same key
    if(temp_node.first != ""){
      new_map.add(temp_node);    
    }
  }
  return new_map;
}

#endif
  
