#include <iostream>
#include<string>
#include<vector>

using std::cout;using std::endl;using std::cin;
using std::vector;
using std::string;

#include "splitter-functions.h"

/*
 * 
 */
int main() {
    string splitString;
    char delim;
    vector <string> splitResult;
    cin >> splitString >> delim;

    splitResult = split(splitString,delim);
    print_vector(cout, splitResult);
    
    return 0;
}