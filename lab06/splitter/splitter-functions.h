/* 
 * File:  splitter-functions.h
 * Author: ben
 *
 * Created on Feb 21, 2018, 12:14 PM
 */
#ifndef EXTRA_H
#define	EXTRA_H
#include<string>
using std::string;
#include<vector>
using std::ostream;
using std::vector;

vector<string> split(const string &s, char separator=' ');
void print_vector(ostream &out, const vector<string> &v);

#endif	/* EXTRA_H */

