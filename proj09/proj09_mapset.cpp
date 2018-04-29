/**************************************
 * File:  proj09_mapset.cpp
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on April 4, 2018, 1:48 PM
 **************************************/
#include "proj09_mapset.h"
#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<algorithm>
using std::copy; using std::lower_bound;
#include<initializer_list>
#include<sstream>
using std::initializer_list; using std::cout;

//constructor for MapSet that adds each new pair into the
//vector in the correct place
//param: initializer list of pairs to add to vector
MapSet::MapSet(initializer_list< pair<string,long> > list_vals){
  //loops through each pair in the initializer list
  for(auto pair_val: list_vals){
    //calls the add function
    add(pair_val);
  }
}

//function used in lower_bound to compare string and pair
//returns a boolean depending on how string compares
//params: a pair in vector to compare, and the key string
bool LowBound(pair<string,long> test_pair, string key){
  //checks if the string in pair is less than key
  if(test_pair.first < key){
    return true;
  }
  return false;
}

//finds where in the vector a pair is that matches key string
//returns the iterator in the vector pair where a match is found
//parameter is the key string to check
vector< pair <string, long> >::iterator MapSet::find_key(string key){
  vector< pair <string, long> >::iterator itr;
  //uses lower_bound algorithm and calls a function within lowerbound
  itr = lower_bound(v_.begin(), v_.end(), key, LowBound);
  return itr;
}

//gets the size of the MapSet
//returns a size_t type which is size of map
size_t MapSet::size(){
  size_t size_map = v_.size();
  return size_map;
}

//returns the pair of values that matches given key
//param is the key that user gives to find a matching pair
pair<string,long> MapSet::get(string key){
  pair<string,long> return_pair = {"",0};
  auto itr = find_key(key);
  //checks if the iterator is not the end
  if(itr != v_.end()){
    //checks if the pair matches the key
    if(itr -> first == key){
      return_pair = *itr;
    }
  }
  return return_pair;
}

//returns a bool, true if map updates with key and val
//params: key and val pair that updates in the map
bool MapSet::update(string key,long val){
  auto itr = find_key(key);
  //checks if the lower bound is not out of map
  if(itr != v_.end()){
    //checks if the key is in the map
    if(itr -> first == key){
      itr -> second = val;
      return true;
    }
  }
  return false;
}

//returns a bool, true if key-val pair is removed
//parameter is the key that we want to remove from map
bool MapSet::remove(string key){
  auto itr = find_key(key);
  //checks if the lower bound is not out of map
  if(itr != v_.end()){
    //checks if the key is in the map
    if(itr -> first == key){
      //erases key-val pair from map
      v_.erase(itr);
      return true;
    }
  }
  return false;
}

//returns a bool, true if key-val pair successfully added
//parameter is a new pair to be added to map
bool MapSet::add(pair<string,long> key_pair){
  string str_key = key_pair.first;
  auto itr = find_key(str_key);
  //checking where iterator points to in the map
  if(itr == v_.end()){
    v_.insert(itr, key_pair);
    return true;
  }else if(itr -> first == str_key){
    //if key already exists in map
    return false;
  }else{
    v_.insert(itr, key_pair);
    return true;
  }
}

//returns an int telling which map is larger
//params are the map to check against calling map
int MapSet::compare(MapSet& map_1){
  long smallest = size();
  //determines which map is smallest
  if(map_1.size() < size()){
    smallest = map_1.size();
  }

  //loops through smallest map
  for(int i=0; i < smallest; i++){
    string arg_str = map_1.v_[i].first;
    string call_str = v_[i].first;
    //compares strings in pairs
    if(arg_str > call_str){
      return -1;
    }else if(call_str > arg_str){
      return 1;
    }
  }
  //if arg map is larger than calling
  if(map_1.size() < size()){
    return 1;
  }else if(map_1.size() > size()){
    return -1;
  }
  return 0;
}

//returns a MapSet which is a union of two maps
//parameter is map to combine with calling map
MapSet MapSet::mapset_union (MapSet& arg_map){
  MapSet new_map;
  new_map.v_ = arg_map.v_;
  //loops through calling map and adds to new map
  for(int i=0; i < v_.size(); i++){
    string call_str = v_[i].first;
    long call_val = v_[i].second;
    //if the pair in calling map already in new map
    if(!new_map.add(v_[i])){
      //updates with calling data (overrides)
      new_map.update(call_str,call_val);
    }
  }
  return new_map;
}

//returns a MapSet which is an intersection of two maps
//parameter is map to find intersection with calling map
MapSet MapSet::mapset_intersection(MapSet& arg_map){
  MapSet new_map;
  long smallest = size();
  //looks to find the smallest map for loop
  if(arg_map.size() < size()){
    smallest = arg_map.size();
  }
  //loops through maps and finds which pairs match
  for(int i=0; i < smallest; i++){
    string arg_str = arg_map.v_[i].first;
    pair<string,long> temp_pair;
    temp_pair = get(arg_str);
    //true if both maps have same key
    if(temp_pair.first != ""){
      new_map.add(temp_pair);    
    }
  }
  return new_map;
}

//returns an ostream of MapSet values formatted
//parameters are ostream and the map to print
ostream& operator<<(ostream& oss, MapSet& arg_map){
  //loops through each pair in the map
  for(int i=0; i < arg_map.v_.size(); i++){
    oss << arg_map.v_[i].first << ":";
    oss << arg_map.v_[i].second;
    //prevents final comma from printing
    if(i != arg_map.v_.size() -1){
      oss << ", ";
    };
  }
  return oss;
}

