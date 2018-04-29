/**************************************
 * File:   proj07_functions.cpp
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on March 18, 2018, 1:30 PM
 **************************************/
//including libraries
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using ServerData = std::map<std::string, std::set<std::string> >;
using std::ifstream; using std::getline; using std::string;
using UserName = const std::string &;
using ServerName = const std::string &;
using std::istringstream; using std::invalid_argument;
using std::domain_error; using std::sort;
using std::set_intersection; using std::set_symmetric_difference;
using std::inserter;
using std::cout; using std::cin; using std::endl; using std::copy_n;

//includes header file for functions
#include "proj07_functions.h"

//no return. Function prints the entire map to a ostream
//parameters are the ostream and the map that we want
//to print out
void PrintAll(std::ostream &os, const ServerData &sd){
    //iterates through every key in the Server Data
    for(auto elem : sd){
      os << elem.first << " :";
      //iterates through each value for every single key
      for(auto set_elem : elem.second){
        os << " " << set_elem;
      }
      //adds new line for each key:valuelist pair
      os << endl;
    } 
}

//returns a boolean value. Function returns true if connection
//was successfully added. Creates new server if necessary
//parameters are the map of server data, server name, and username
bool AddConnection(ServerData &sd, ServerName sn, UserName un){
  auto iterator = sd.find(sn);
  //if the server exists within the server data
  if(iterator != sd.end()){
    //checks if user is already connected to server
    if(sd[sn].find(un) != sd[sn].end()){
        return false;
    }  
    //adds user to server
    sd[sn].insert(un);
  }
  
  //if server does not exist, creates new server
  if(iterator == sd.end()){
    sd[sn].insert(un);
  }
  return true;
}

//returns a boolean: whether user is successfully disconnected.
//function deletes designated user from the given server
//param: map of server data, server name, and user name
bool DeleteConnection(ServerData &sd, ServerName sn, UserName un){
  auto iterator = sd.find(sn); 
  //if the servername exists in server data
  if(iterator != sd.end()){
    //checks if the user is not connected to the server
    if(sd[sn].find(un) == sd[sn].end()){
        return false;
    }  
    //removes user from server
    sd[sn].erase(un);
  }
  return true;
}

//returns a map of server data
//function parses a .txt file and makes adds/removes users
//from server data depending on data in file
//parameter is the name of the .txt to be parsed
ServerData ParseServerData(const std::string &fname){
  ServerData sd;
  ifstream file(fname);
  string str;
  string action;
  string word;
  //checks if .txt file can be opened
  if(file.fail()){
    throw invalid_argument("failed");
  }else{
    //keeps parsing line by line until no more lines
    while(getline(file,str)){
      istringstream buf(str);
      std::vector<string> v;
      //parses each line word by word
      while(buf >> word){
        v.push_back(word);
      }
      //designated action words
      ServerName server_name = v[2];
      action = v[1];
      UserName user_name = v[0];

      //checks action word and either deletes or adds
      if(action == "join"){
        AddConnection(sd, server_name, user_name);
      }else if(action == "leave"){
        DeleteConnection(sd, server_name, user_name);
      }else{
        //throws error if action word not "leave" or "join"
        throw domain_error("command not leave or join");
      }
    }
  }
  return sd;
}

//returns a set of all servers in the server data
//parameter is the server data we want to check
std::set<std::string> AllServers(const ServerData &sd){
   std::set<std::string> all_servers;
   //loops through every server key in server data
   for(auto elem : sd){
      all_servers.insert(elem.first);
    }
   return all_servers;
}

//returns a set of all users in the server data
//parameter is the server data we want to check
std::set<std::string> AllUsers(const ServerData &sd){
  std::set<std::string> all_users;
  //iterates through ever server name in server data
  for(auto elem : sd){
    //iterates through each user in the server
    for(auto set_elem : elem.second){
        all_users.insert(set_elem);
    }
  }
  return all_users;
}

//returns a set of all servers with a specific user connected
//parameters are the server data to check, and username to check
std::set<std::string> HasConnections(const ServerData &sd, UserName un){
  std::set<std::string> connected_servers;
  //iterates through each server in the server data
  for(auto elem : sd){
    //iterates through each user in each server
    for(auto set_elem : elem.second){
      //if the user is connected in the server
      if(set_elem == un){
        connected_servers.insert(elem.first);
        break;
      }
    }
  } 
  return connected_servers;
}

//returns a set of all users that are connected to specific server
//parameters are the server data to check, and server to check
std::set<std::string> HasUsers(const ServerData &sd, ServerName sn){
  std::set<std::string> connected_users;
  auto finder = sd.find(sn);
  //if the given server exists in the server data
  if(finder != sd.end()){
    //iterates through ever user in the server
    for(auto set_elem : finder -> second){
      connected_users.insert(set_elem);
    }
  }
  return connected_users;
}

//no return value. Sets equal user numbers on each server
//parameters are the server data, and the two servers to "balance"
void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2){
  std::set<std::string> set_1 = HasUsers(sd,sn1);
  std::set<std::string> set_2 = HasUsers(sd,sn2);
  long size;
  std::set<std::string> new_set, new_set_1, new_set_2, same_set;
  //finds all users that are only connected to one of the servers
  set_symmetric_difference(set_1.begin(),set_1.end(), set_2.begin(),
    set_2.end(),inserter(new_set, new_set.begin()));
  //finds all users that are connected to both of the servers
  set_intersection(set_1.begin(),set_1.end(), set_2.begin(), set_2.end(), 
    inserter(same_set, same_set.begin()));

  //designates how many users in first server (even or odd)
  if((new_set.size() % 2) == 0){
    size = new_set.size() / 2;
  }else{
    size = (new_set.size() / 2) + 1;
  }
  //copys the first half of all unique users to first set
  copy_n(new_set.begin(), size, inserter(new_set_1,new_set_1.begin()));
  //copys the second half of all unique users to second set
  set_symmetric_difference(new_set_1.begin(),new_set_1.end(), new_set.begin(),
   new_set.end(),inserter(new_set_2,new_set_2.begin()));
  //adding the shared users to each new server set
  new_set_1.insert(same_set.begin(), same_set.end());
  new_set_2.insert(same_set.begin(), same_set.end());
  //clearing unbalanced server sets
  sd[sn1].clear();
  sd[sn2].clear();
  //adding balanced server set to the server
  sd[sn1].insert(new_set_1.begin(), new_set_1.end());
  sd[sn2].insert(new_set_2.begin(), new_set_2.end());
}

//no return. Function cleans duplicate users and balances the 
//servers in a round robin fashion (alphabetically)
//parameter is just the server to clean and balance
void CleanAndBalance(ServerData &sd){
  std::set<std::string> connected_servers;
  std::set<std::string> all_users = AllUsers(sd);
  std::set<std::string> all_servers = AllServers(sd);
  std::set<std::string> balanced_users;
  std::set<std::string> balanced_servers;

  //iterates through all users and removes
  //if in multiple servers
  for(auto user: all_users){
    connected_servers = HasConnections(sd, user);
    long connected_size = connected_servers.size();
    //if the user is connected to more than one server
    if(connected_size > 1){
      for(auto server: connected_servers){
        //makes sure user is still connected to one server
        if(connected_size == 1){
          break;
        }else{
          connected_size--;
          //removes the duplicate user from server
          DeleteConnection(sd, server, user);
        }
      }
    }
  }
  all_users = AllUsers(sd);
  //iterates through every existing server
  for(auto serv : all_servers){
    //clears all server data
    sd[serv].clear();
  }
  //size of all existing users
  long size = all_users.size();
  //iterates through every existing user
  //and sorts them into servers in round-robin fashion
  while(size > 0){  
    //iterates through all existing servers
    for(auto server: all_servers){
      //if no more users to put in server
      if(all_users.size() == 0){
        break;
      }
      //adds user to server and removes from "wait list"
      AddConnection(sd, server, *all_users.begin());
      all_users.erase(*all_users.begin());
    }
    size --;
  }
}
