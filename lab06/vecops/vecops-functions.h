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

vector<long> vector_ops(const vector<long>& v1, const vector<long>& v2, char op);
void print_vector(ostream &out, const vector<long> &v);
#endif	/* EXTRA_H */

