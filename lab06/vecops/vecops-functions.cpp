/* 
 * File:   vecops-functions.cpp
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

#include"vecops-functions.h"

vector <long> vector_ops(const vector<long>& v1, const vector<long>& v2, char op){
    vector <long> shortest;
    vector <long> longest;
    vector <long> opVec;
    int cnt = 0;
    if(v1.size() > v2.size()){
        shortest = v2;
        longest = v1;
    }else{
        shortest = v1;
        longest = v2;
    }
    if(op != '+' && op != '-'){
        return opVec;
    }
    
    for(int i = 0; i < shortest.size(); i++){
        if(op == '+'){
            opVec.push_back(v1[i] + v2[i]);
            cout << opVec[i] << endl;
        }
        else if (op == '-'){
            opVec.push_back(v1[i] - v2[i]);
        }
    }
    
    for(int i = shortest.size(); i < longest.size(); i++){
        opVec.push_back(longest[i]);
    }
    
    
    return opVec;
    
}

void print_vector(ostream &out, const vector<long> &v){
    for(int i = 0; i < v.size(); i++){
        out << v[i] << endl;
    }
    
}