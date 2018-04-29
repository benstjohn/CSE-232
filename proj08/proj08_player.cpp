/**************************************
 * File:   proj08_player.cpp
 * Author: Ben St. John
 * Section: 006
 * 
 * Created on March 25, 2018, 1:39 PM
 **************************************/
#include<string>
#include<iomanip>
#include<iostream>
#include<sstream>
using std::string; using std::ostringstream; using std::endl;
using std::fixed; using std::setprecision; using std::cout;
#include "proj08_market.h"
#include "proj08_player.h"

//return true if player has enough cash to buy stocks
//parameters: market with all stocks, the symbol for the stock
//that player wants to buy, date of stock, quantity of stocks
bool Player::buy(Market &m, string stock, long date, long qty){
  double price = m.get_price(stock, date);
  double cash_needed = price * qty;
  //checks if player has enough cash to buy stocks
  if(cash >= cash_needed){
    vector<string> v = m.symbol_list;
    map<long, vector<double> > stock_map = m.stocks;
    vector<string>::iterator itr = find(v.begin(), v.end(), stock);
    //if the symbol of stock is a valid symbol
    if(itr != v.cend()){
        auto map_finder = stock_map.find(date);
      //checks if the date for stock is valid
      if(map_finder != stock_map.end()){
        long stocks_owned;
        auto stock_finder = stocks.find(stock);
        cash = cash - cash_needed;
        //checks to see if user already owns this stock
        if(stock_finder != stocks.end()){
          stocks_owned = stock_finder -> second;
          stocks_owned += qty;
          stock_finder -> second = (stocks_owned);
        }else{
          stocks.insert({stock, qty});
        }
          return true;
      }
    }
  }
  return false;
}

//return bool, true if user successfully sells their stocks
//params: marketplace of stocks, stock symbol to sell, 
//date to sell (to know price), and number to sell
bool Player::sell(Market &m, string stock, long date, long qty){
  double price = m.get_price(stock, date);
  vector<string> v = m.symbol_list;
  map<long, vector<double> > stock_map = m.stocks;
  vector<string>::iterator itr = find(v.begin(), v.end(), stock);
  //checks if the stock symbol is valid
  if(itr != v.cend()){
    auto map_finder = stock_map.find(date);
    //checks if the date for stock is valid
    if(map_finder != stock_map.end()){
      long stocks_owned;
      auto stock_finder = stocks.find(stock);
      //makes sure the user owns the stocks
      if(stock_finder != stocks.end() ){
        stocks_owned = stock_finder -> second;
        //makes sure user has the right amount to sell
        if(stocks_owned >= qty){
          stocks_owned -= qty;
          stock_finder -> second = (stocks_owned);
          cash += price * qty;
          return true;
        }
      }
    }
  }
  return false;
}

//returns a formatted string of players data (cash and stocks)
//params: none
string Player::to_str(){
  ostringstream oss;
  oss << fixed << setprecision(2);
  oss << cash << ",";
  //if the user owns any stocks
  if(stocks.size() > 0){
    //loops through each stock user owns
    for(auto elem: stocks){
      //formats the stocks and quantity of stocks
      oss << elem.first << ":";
      oss << elem.second << ',';
    }
  }
  string s = oss.str();
  return s.substr(0, s.size() - 1);
}

//returns a new player instance of two combined players
//parmas: A player instance to combine with the calling player
Player Player::combine(Player& p2){
  map<string, long > total_stocks;
  //combines the two players cash values
  double total_cash = p2.cash + cash;
  Player new_player(total_cash);
  //clears the individual cash values
  p2.cash = 0;
  cash = 0;
  //combines two players stocks into one stock map
  total_stocks.insert(p2.stocks.begin(), p2.stocks.end());
  total_stocks.insert(stocks.begin(), stocks.end());
  new_player.stocks = total_stocks;
  //clears the individual stock values
  p2.stocks.clear();
  stocks.clear();
  return new_player;
}