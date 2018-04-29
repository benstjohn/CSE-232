/* 
 * File:   lab07_functions.cpp
 * Author: ben
 *
 * Created on Feb 28, 2018, 12:30 PM
 */

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<sstream>

using std::cout;using std::endl;using std::cin;
using std::vector;
using std::string;
using std::getline;
using std::setw;
using std::right;
using std::ostringstream;


using matrix_row = vector <long>;
using matrix = vector <matrix_row>;

#include"lab07_functions.h"

string matrix_to_str(const matrix &m1, size_t width){
    ostringstream stream;
    
    for(int i = 0; i < m1.size(); i++){
        for(int j = 0; j < m1[i].size(); j++){
            stream << right << setw(width) << m1[i][j];
        }
        stream << endl;
    }
    string s = stream.str();
    s = s.substr(0,s.length() - 1);
    return s;
}

bool same_size(matrix &m1, matrix &m2){
    for(int i = 0; i < m1.size(); i++){
        if(m1[i].size() == m2[i].size()){

        }else{
            return false;
        }
    }

    for(int i = 0; i < m2.size(); i++){
        if(m1[i].size() == m2[i].size()){

        }else{
            return false;
        }
    }

    return true;
}

matrix add(matrix &m1, matrix &m2){
    matrix_row new_row;
    matrix new_matrix;
    if(same_size(m1,m2)){
      for(int i = 0; i < m1.size(); i++){
        for(int j = 0; j < m1[i].size(); j++){
            new_row.push_back(m1[i][j] + m2[i][j]);
        }
        new_matrix.push_back(new_row);
        new_row.clear();
      }
    }

    return new_matrix;
}

matrix scalar_multiply(matrix &m, long val){
    matrix_row new_row;
    matrix new_matrix;

    for(int i = 0; i < m.size(); i++){
      for(int j = 0; j < m[i].size(); j++){
        new_row.push_back(m[i][j] * val);
      }
      new_matrix.push_back(new_row);
      new_row.clear();
    }
    
    return new_matrix;

}