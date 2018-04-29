/**************************************
 * File:  proj08_market.cpp
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on March 25, 2018, 1:48 PM
 **************************************/
#include<map>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include<utility>

using std::ifstream; using std::getline; using std::map;
using std::istringstream; using std::invalid_argument;
using std::string; using std::ifstream; using std::vector;
using std::pair; using std::cout; using std::to_string;
using std::stol; using std::stod; using std::endl;
#include "proj08_market.h"

//constructur for the market struc
//parses through a file of stocks and puts them
//into a map in a market struct
//params: the name of file to parse
Market::Market(string s){
  file_name = s;
  //creates new filestream with string
  ifstream file(file_name);
  string date,str,word;
  //checks if .txt file can be opened
  if(file.fail()){
    //throws error if file can't be opened
    throw invalid_argument("failed");
  }else{
    //loops through each line of the file of all stocks
    while(getline(file,str)){
      pair<long, vector<double> > stock_map;
      istringstream buf(str);
      //parses each line word by word
      buf >> word;
      date = word;
      stock_map.first = stol(date);
      //loops through each stock and adds to a new map
      while(buf >> word){
        stock_map.second.push_back(stod(word));
      }
     //adds a dates worth of stocks as new item into map
     this -> stocks.insert(stock_map); 
   }
  }
}

//returns a double: -1 if stock doesn't exist, or a price
//value for a stock based on given symbol and date
//params: stock symbol and date to check
double Market::get_price(string symbol, long date) const{
  vector<string> v = this -> symbol_list;
  map<long, vector<double> > stock_map = this -> stocks;
  vector<string>::iterator itr = find(v.begin(), v.end(), symbol);
  long symbol_loc;
  double price;
  //checks to see if given stock symbol is valid
  if(itr != v.cend()){
    auto map_finder = stock_map.find(date);
    //if the date is a valid date
    if(map_finder != stock_map.end()){
      symbol_loc = std::distance(v.begin(), itr);
      //gets the price of stock at date
      price = map_finder -> second[symbol_loc];
      return price;
    }
  }
  return -1.0;
}

//returns a pair of doubles, high price and low price
//params: the year and the symbol that we are looking for the
//high and the low prices
pair<double, double> Market::high_low_year(long year, string symbol){
  double high = 0.0;
  double low = 100000.0;
  pair<double,double> high_low;
  vector<string> v = this -> symbol_list;
  map<long, vector<double> > stock_map = this -> stocks;
  vector<string>::iterator itr = find(v.begin(), v.end(), symbol);
  long symbol_loc;
  long date;
  string year_str = to_string(year);
  double price;
    //checks if stock symbol is valid
    if(itr != v.cend()){
        //loops through every date of users stocks
        for(auto stock_date : stock_map){
            date = stock_date.first / 10000;
            //checks if date is same as given year
            if(date == year){
                //finds index of symbol within date
                symbol_loc = std::distance(v.begin(), itr);
                price = stock_date.second[symbol_loc];
                //checks if price is higher than high
                if(price > high){
                    high = price;
                }
                //checks if price is lower than low
                if (price < low){
                    low = price;
                }
            }
        }  
        //if high and low didn't change
        if(high == 0.0 && low == 100000.0){
          return {-1.0, -1.0};
        }
        return {high,low};
    }
    return {-1.0, -1.0};
}