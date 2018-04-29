
#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;

#include "proj11_mapset.h"





/*
auto bool_result = ms.remove("alan");
auto pr = ms.get("abby");
string key = pr.first; string key_ans = "";

bool_result = ms.remove("abby");

ostringstream oss;
oss << ms;
string ans = "abby:3, alan:2";
string str_result = oss.str();
cout << str_result;
*/



int main (){
  
MapSet<string,long> ms({ {"bill",1},{"alan",2},{"abby",3} });

auto bool_result = ms.remove("bill");
auto pr = ms.get("bill");

bool_result = ms.remove("irving");

ostringstream oss;
oss << ms;
string ans = "abby:3, alan:2";
string str_result = oss.str();
std::cout << str_result;
  
}
