/**************************************
 * File:   proj06_functions.cpp
 * Author: Ben St. John
 *
 * Created on March 7, 2018, 1:30 PM
 **************************************/

//including libraries
#include<string>
using std::string;
#include<vector>
#include<iostream>
#include<sstream>
using std::vector;using std::ostringstream; 
using std::cout; 
using std::endl; using std::swap; using std::to_string;

//including header file for functions
#include "proj06_functions.h"

//returns a string of the vector, separated by commas
//parameter is a vector of longs
string vec_2_str(const vector<long>& v){
  ostringstream oss;
  string vec_str = "";
  //iterates through given vector v and will
  //add each long to a comma separated string.
  //Loop uses ostringstream to make longs a string 
  for(int i=0; i < v.size(); i++){
    oss << v[i];
    vec_str += oss.str();
    vec_str += ",";
    //resetting and clearing stringstream
    oss.str("");
    oss.clear();
  }
  //removing the last comma in the string
  vec_str = vec_str.substr(0, vec_str.size() - 1);
  return vec_str;
}

//returns a vector of longs that is the nstep vector
//parameters are highest number the sequence will go
//to and the nstep for which the vector will follow.
vector<long> gen_nstep_vector (long limit, long nstep){
  vector<long> nstep_vector;
  bool finished_gen = 0;
  //initializes vector with {1,1}
  nstep_vector.push_back(1);
  nstep_vector.push_back(1);
  //this loops generates all of the seed values
  //for the nstep vector. Each value is sum of
  //all the previous
  for(int i=2; i < nstep; i++){
    long next_val = 0;
    //this loops sums up all previous values
    //in the vector to create next seed
    for(int j=0; j < nstep_vector.size(); j++){
      next_val += nstep_vector[j];
    }
    //adds the next seed to nstep
    nstep_vector.push_back(next_val);
  }

  int n_index = nstep;
  //this loops will keep adding new values to
  //nstep vector until it reaches the given limit
  while(!finished_gen){
    long next_val = 0;
    //loops through and creates a sum of the 
    //previous 'n' items in the vector
    for(int j=1; j <= nstep; j++){
      next_val += nstep_vector[n_index - j];
    }
    //checks if the newly generated value
    //is greater than the given limit
    if(next_val > limit){
      finished_gen = 1;
    }else{
      nstep_vector.push_back(next_val);
    }
    n_index++;
  }
      
  return nstep_vector;
}

//returns a string that is a binary encoding
//of a number, using a generated nstep vector
//parameters are num to be encoded and the 
//nstep key to generate the encoding vector
string num_to_nstep_coding(long num, long nstep){
  vector<long> n_step = gen_nstep_vector(num, nstep);
  string coded_string = "";
  //loops through entire vector backwards to
  //find the best values in vector that add
  //up to the given num
  for(int i = n_step.size() - 1; i > 0; i--){
    //checks if value can be part of sum
    if(num - n_step[i] >=0){
      num -= n_step[i];
      coded_string += '1';
    }else{
      coded_string += '0';
    }
  }
  //string is backwards - need to flip it
  long len = coded_string.length(); //length of string
  //looping through the chars and swapping
  for (int i=0; i<len/2; i++){
    swap(coded_string[i], coded_string[len-i-1]);
  }
  return coded_string;
}

//returns a long that is decoded using a nstep vector
//parameters are the encoding of the long and the
//long vector that was used to create encoding
long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence){
  int final_num = 0;
  //loops through every item in the encoding
  //vector and creates a running total of used
  //values to find the encoded num
  for(int i=0; i < nstep_sequence.size(); i++){
    //uses coding to see if value is part of sum
    if(coding[i] == '1'){
      final_num += nstep_sequence[i + 1];
    }
  }
  return final_num;
}
