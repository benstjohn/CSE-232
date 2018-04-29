//Ben St. John
//Section 006
//February 8, 2017
//Project 4
#include<iostream>
using std::cout; using std::cin; using std::endl; 
using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<cmath>
using std::swap;

//all necessary characters for symbolizing
const string the_chars = "0123456789abcdef"; 

//Functions for the program

//Flips a string backwards
string reverse_string(string str){
  long len = str.length(); //length of string

  //looping through the chars and swapping
  for (int i=0; i<len/2; i++){
    swap(str[i], str[len-i-1]);
  }
  
  return str;
}

//Checks if string is palendrome
bool is_palindrome(string str){

  //calls the reverse_string function
  if(reverse_string(str) == str){
    return true;
  }
    return false; 
}

//converting long to specified base
string long_to_base(long n, long base){
  long remainderN = 0; //instantiate remainder
  string newStr = ""; //instantiate string

  //loops through until n is negative
  while(n > 0){
    remainderN = n % base;
    newStr += the_chars[remainderN]; //finds char from const
    n = n/base;
  }
  newStr = reverse_string(newStr);
  return newStr; //returns converted string
}

//checks if number is divisible only by 1 and itself
bool is_prime(long my_l){
  //iterates through long
  for(int i = 2; i <= my_l; i++){
    //if number is divisible by something else
    if(my_l % i == 0 && i != my_l){
      return false;
    }
  }
  return true;
}

//checks a converted long to see if palendrome and prime
string is_pal_prime(long my_l){
  string binaryStr = long_to_base(my_l, 2); //binary
  string decStr = long_to_base(my_l, 10); //decimal
  string hexStr = long_to_base(my_l, 16); //heaxdecimal

  //checks is long is prime
  if(is_prime(my_l)){
    if(is_palindrome(binaryStr)){ //if binary
      return "binary-pal-prime";
    }
    else if(is_palindrome(decStr)){ //if decimal
      return "decimal-pal-prime";
    }
    else if(is_palindrome(hexStr)){ //if hexidecimal
      return "hex-pal-prime";
    }
  }
  return "not-pal-prime"; //if no conditionals true
}

//main function given by instructor
int main (){
  long test_num;
  cin >> test_num;
  cout << boolalpha;

  switch(test_num) {

  case 1: {
    string input;
    cin >> input;
    cout << reverse_string(input);
    break;
  }

  case 2:{
    string input;
    cin >> input;
    cout << is_palindrome(input);
    break;
  }

  case 3:{
    long n, base;
    cin >> n >> base;
    cout << long_to_base(n,base);
    break;
  }

  case 4:{
    long n;
    cin >> n;
    cout << is_prime(n);
    break;
  }

  case 5:{
    long n;
    cin >> n;
    cout << is_pal_prime(n);
    break;
  }
    
  } // of switch
}  // of main