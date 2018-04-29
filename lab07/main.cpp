#include<vector>
#include<string>
#include "lab07_functions.h"
#include<iostream>
using std::cout;

int main(){
    matrix m={ {0,1}, {1,2} };
    string s = matrix_to_str(m);
    m = { {1,1,1}, {2,2,2}, {3,3,3} };
    s = matrix_to_str(m,2);
    cout << s;
}

