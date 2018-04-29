/**************************************
 * File:   proj05_functions.cpp
 * Author: Ben St. John
 *
 * Created on Feb 24, 2018, 12:30 PM
 **************************************/

//inlcuding libraries
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using std::cout;using std::endl;using std::cin;
using std::vector;
using std::string;
using std::getline;
using std::istringstream;

//including header file for functions
#include"proj05_functions.h"

//constant that holds all chars of alphabet except 'q'
const string kAlpha = "abcdefghijklmnoprstuvwxyz";

//returns a string that is all alpha and lowercase
//parameter is a string of input from the user
string clean_string(string s){
  string clean = "";
  //iterates through given string s and will
  //add char to clean string if it is alpha.
  //Also, the loop will lowercase each char 
  for(int i = 0; i < s.length(); i++){
    //checking if char is alpha and not a space
    if(isalpha(s[i]) && s[i] != ' ') {
      s[i] = tolower(s[i]);
      clean.push_back(s[i]);
    }
  }
  return clean;
}

//returns an encoded string based off of the given
//string and a diagraph of the alphabet. 
//parameter is an initial string to be encoded
string create_encoding(string key){
  //cleans key by calling 'clean_string' function on it
  string cleaned_str = clean_string(key);
  string encoded_str = "";
  int key_count = 0;
  int i = 0;
  int count = 0;
  //first loop iterates through key string and will
  //add each character to the encoded string only one time,
  //skipping all duplicates. Final string cannot include
  //the letter 'q'
  while(key_count < cleaned_str.length()){
    //checks if character has already been added in encoding
    if(encoded_str.find(cleaned_str[key_count]) > 25){
      //if char is 'q', it will not add to encoding
      if(cleaned_str[key_count] != 'q'){
        encoded_str.push_back(cleaned_str[key_count]);
        count ++;
      }
    }
    key_count ++;
  }
  //second loop will add the rest of the alphabet to the
  //encoded string, until the string reaches a length of 25.
  //No letter will be duplicated in the string. 
  //'q' not included
  while(count < 25){
    //iterates through const string of alphabet
    if(encoded_str.find(kAlpha[i]) > 25){
      encoded_str.push_back(kAlpha[i]);
      count ++;
    }
    i++;
  }
  return encoded_str;
}

//returns a string of two characters, which are encoded versions
//of the given characters. Parameters are a key digraph pair
//that should be encoded, and the two block strings help
//assist in the encoding of the digraph.
string encode_digraph(string dg, string block1, string block2){
  //encodes both blocks using 'create_encoding' function 
  string string_1 = create_encoding(block1);
  string string_2 = create_encoding(block2);
  //using algebra to determine row and column of first
  //encoded digraph character.
  long row_1 = kAlpha.find(dg[0]) / 5;
  long col_1 = kAlpha.find(dg[1]) % 5;
  long index_1 = row_1 * 5 + col_1;
  //using algebra to determine row and column of second
  //encoded digraph character.
  long row_2 = kAlpha.find(dg[1]) / 5;
  long col_2 = kAlpha.find(dg[0]) % 5;
  long index_2 = row_2 * 5 + col_2;
  
  string final;
  //pushing both digraph chars into a single string 
  final.push_back(string_1[index_1]);
  final.push_back(string_2[index_2]);
  return final;
}

//returns a string of two characters, which are decoded versions
//of the given digraph. Parameters are a key digraph pair
//that should be decoded, and the two block strings help
//assist in the encoding of the digraph. This function
//is the reverse of encode_digraph
string decode_digraph(string dg, string block1, string block2){
  //encodes both blocks using 'create_encoding' function
  string string_1 = create_encoding(block1);
  string string_2 = create_encoding(block2);
  //using algebra to determine row and column of first
  //decoded digraph character.
  long row_1 = string_1.find(dg[0]) / 5;
  long col_1 = string_2.find(dg[1]) % 5;
  long index_1 = row_1 * 5 + col_1;
  //using algebra to determine row and column of second
  //decoded digraph character.
  long row_2 = string_2.find(dg[1]) / 5;
  long col_2 = string_1.find(dg[0]) % 5;
  long index_2 = row_2 * 5 + col_2;
  //pushing both digraph chars into a single string 
  string final;
  final.push_back(kAlpha[index_1]);
  final.push_back(kAlpha[index_2]);
  return final;
}

//function returns an string which is an encoded version
//of a message input from user. Parameters include
//the users message, and the two key strings the user
//wishes to use as blocks for the encoding pattern.
string encode(string msg, string key1, string key2){
  string final_encode = "";
  string encoded_str = "";
  string digraph = "";
  //cleans message using 'clean_string' function
  msg = clean_string(msg);
  //if length of msg is odd, add x to the end to make even
  if(msg.length() % 2){
      msg.push_back('x');
  }
  //iterates through the message and pulls two
  //consecutive characters at a time, and encodes
  //them using encode_digraph function. Loop ends
  //when entire message has been encoded.
  for(int i = 0; i < msg.length(); i += 2){
      digraph = msg.substr(i, 2);
      encoded_str = encode_digraph(digraph, key1, key2);
      final_encode.append(encoded_str);
  }
  return final_encode;
}

//function returns an string which is a decoded version
//of a message input from user. Parameters include
//the encoded message, and the two key strings the user
//wishes to use as blocks for the decoding pattern.
string decode(string msg, string key1, string key2){
  string final_decode = "";
  string decoded_str = "";
  string digraph = "";
  //cleans encoded message with 'clean_string' function
  msg = clean_string(msg);
  //if length of msg is odd, add x to the end to make even
  if(msg.length() % 2){
      msg.push_back('x');
  }
  //iterates through the message and pulls two
  //consecutive characters at a time, and decodes
  //them using decode_digraph function. Loop ends
  //when entire message has been decoded.
  for(int i = 0; i < msg.length(); i += 2){
      digraph = msg.substr(i, 2);
      decoded_str = decode_digraph(digraph, key1, key2);
      final_decode.append(decoded_str);
  }
  return final_decode;
}