#include "lab10_circbuf.h"

#include<iostream>
#include<sstream>
#include<string>
using std::ostringstream;
using std::ostream;
#include<vector>
#include<algorithm>
using std::vector;
using std::string;
using std::runtime_error;
using std::range_error;


  CircBuf::CircBuf(size_t s){
      sz_ = s;
      cnt_ = 0;
      buf_ = vector<long>(s,0);
      head_ = 0;
      tail_ = 0;
  }

  CircBuf::CircBuf(initializer_list<long> list, size_t s){
    if(list.size() > s){
      throw runtime_error("houston, we have a problem");
    }else{
      sz_ = s;
      cnt_ = list.size();
      head_ = 0;
      tail_ = cnt_;
       buf_ = vector<long>(s,0);
      copy(list.begin(), list.end(), buf_.begin());
    }
  }

  
  
  ostream& operator<<(ostream& oss, const CircBuf &cb){
    if(cb.empty()){
      oss << "CircBuf empty";
    }else{
        oss << "Front:" << cb.buf_[cb.head_] << ", ";
        oss << "Back:" << cb.buf_[cb.tail_ - 1] << ", ";
        oss << "Cnt:" << cb.cnt_ << ", ";
        oss << "Sz:" << cb.sz_ << std::endl;

        for(int i=0; i < cb.buf_.size(); i++){
            oss << cb.buf_[i];
            if(i != cb.buf_.size() -1){
                oss << ", ";
            }
        }
    }
    return oss;
  } 

  long CircBuf::front() const{
    if(this -> empty()){
        throw runtime_error("empty");
    }else{
        return buf_[head_];
    }
  }

  long CircBuf::back() const{
    if(this -> empty()){
        throw runtime_error("empty");
    }else{
        return buf_[tail_ - 1];
    }
  }

  bool CircBuf::full() const{
    if(cnt_ == sz_){
        return true;
    }
    return false;
  }

  bool CircBuf::empty() const{
    if(cnt_ == 0){
      return true;
    }
    return false;
  }

  void CircBuf::add(long new_val){
     if(full()){
        throw runtime_error("full");
    }else{
      tail_ = (head_ + cnt_) % sz_;
      buf_[tail_] = new_val;
      tail_ += 1;
      cnt_++;
    }
  }

  void CircBuf::remove(){
    if(this -> empty()){
        throw runtime_error("empty");
    }else{
        if((head_ + 1) >= sz_){
            head_ = 0;
        }else{
         head_ += 1;
        }
        
        cnt_ --;
    }
  }

  /*
  friend CircBuf operator+(CircBuf &buf, long val);
  friend CircBuf operator+(long val, CircBuf &buf);
  friend CircBuf operator+(CircBuf &buf2, CircBuf &buf1);
  */
