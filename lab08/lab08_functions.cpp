#include<vector>
using std::vector;
#include<string>
using std::string;
#include<map>
using std::map;
#include<utility>
#include<stdexcept>
#include<sstream>
#include <iomanip>
using std::ostringstream;
using std::range_error;
using std::pair;
using std::string; 
#include "lab08_functions.h" 
using Collatz = pair<long, vector<long> >;
using CollatzMap = map<long, vector<long> >;


CollatzMap collatz_map;
Collatz collatz_element;

long collatz_next(long n){
    if(n <= 0){
        throw range_error("range_error");
    }else{
        if(n % 2 == 0){
            n /= 2;
        }else{
            n = (n*3) + 1;
        }
        return n; 
    }
}


string Collatz_to_string(const Collatz &p){
    ostringstream oss;
    oss << p.first << ": ";
    for(int i=0; i < p.second.size(); i++){
        oss << p.second[i] << ',';
    }
    string s = oss.str();
    return s.substr(0, s.size() - 1);
}


string sequence_in_map_to_string(map<long, vector<long> > &m, long number){
    string final_str = "";
    if(m.find(number) == m.end()){
        return final_str;
    }else{
        final_str.append(Collatz_to_string(*m.find(number)));
    }
    return final_str;
}


vector<long> collatz_sequence(map<long, vector<long> > &m, long number){
    vector<long> new_vec;
    long next = collatz_next(number);
    auto finder = m.find(number);

    if(finder != m.end()){
        return finder -> second;
    }

    while(next != 1){
        new_vec.push_back(next);
        next = collatz_next(next);
    }
    new_vec.push_back(1);
    
    return new_vec;  

}


void collatz_range(map<long, vector<long> > &m, long low, long high){
    for(int i = low; i <= high; i++){
        m.insert({i,collatz_sequence(m,i)});
    }
}

