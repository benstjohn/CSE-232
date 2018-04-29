#include<string>
using std::string;
#include<cmath>
#include "lab09_vector.h"
#include <sstream>
#include <iostream>
using std::stringstream;
using std::cout;

MathVector::MathVector(long x1, long y1){
    x = x1;
    y = y1;
}

// 4 function members you must write
MathVector MathVector::add (const MathVector& mv_2){
    long v1_x = x;
    long v1_y = y;
    long v2_x = mv_2.x;
    long v2_y = mv_2.y;
    long new_x = v1_x + v2_x;
    long new_y = v1_y + v2_y;

    MathVector new_vector(new_x, new_y);
    return new_vector;
}

MathVector MathVector::mult(long scalar){
    long v1_x = x;
    long v1_y = y;
    long new_x = v1_x * scalar;
    long new_y = v1_y * scalar;

    MathVector new_vector(new_x, new_y);
    return new_vector;
}

long MathVector::mult(const MathVector& mv_2){
    long v1_x = x;
    long v1_y = y;
    long v2_x = mv_2.x;
    long v2_y = mv_2.y;
    long new_x = v1_x * v2_x;
    long new_y = v1_y * v2_y;

    return (new_x + new_y);
}

double MathVector::magnitude(){
    long v_x = x;
    long v_y = y;
    long inside = ((v_x)*(v_x)) + ((v_y)*(v_y));

    double mag = sqrt(inside);

    return mag;
}

string vec_to_str(const MathVector&vec){
    stringstream ss;
    ss << vec.x;
    ss << ":";
    ss << vec.y; 
    return ss.str();
}
