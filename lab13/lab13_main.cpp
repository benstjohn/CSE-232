#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;

#include "lab13_singlelink.h"

int main () {


ostringstream oss;
SingleLink<long> sl(10);
sl.append_back(22);
sl.append_back(33);
bool b = sl.del(22);

oss << sl;
string s = oss.str();
string ans = "10, 33";
std::cout << s;
  
}
