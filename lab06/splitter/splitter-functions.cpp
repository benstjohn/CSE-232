/* 
 * File:   splitter-functions.cpp
 * Author: ben
 *
 * Created on Feb 21, 2018, 12:30 PM
 */

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using std::cout;using std::endl;using std::cin;
using std::vector;
using std::string;
using std::getline;
using std::istringstream;

#include"splitter-functions.h"

vector <string> split(const string &s, char separator){
    string name = "";
    istringstream streaml;
    streaml.str(s);
    vector <string> finalStrings;


    while (getline(streaml,name,separator)){
        finalStrings.push_back(name);
    }
    
    return finalStrings;
}

void print_vector(ostream &out, const vector<string> &v){
    for(int i = 0; i < v.size(); i++){
        out << v[i] << endl;
    }
    
}