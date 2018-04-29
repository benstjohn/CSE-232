#ifndef VEC
#define VEC

#include<string>
#include <algorithm>
#include<initializer_list>
#include<stdexcept>
using std::range_error;
using std::initializer_list;
using std::string; using std::copy; using std::swap;

namespace student {
  template<typename T>
  class vector{
    private:
      T *data_;
      size_t capacity_;
      size_t size_ = 0;
    public:
      vector(size_t capacity = 10):capacity_ (capacity), size_ (0){
          data_ = new T[capacity];
          
      }; 

      vector(initializer_list <T> init):capacity_ (init.size()), size_ (init.size()){
          copy(init.begin(), init.end(), data_);
      }; 
      
      size_t capacity();
      size_t size();
      void push_back(T val);
      T& operator[](size_t val);
      T& front();
      T& back();
      vector(vector& v): capacity_ (v.capacity_), size_ (v.size_){
          copy(v.data_, v.data_ + size_, data_);
      };

      vector& operator=(vector& v);
      ~vector();
      
  };

    template <typename T>
    size_t vector<T>::capacity(){
      return capacity_;
    }

    template <typename T>
    size_t vector<T>::size(){
      return size_;
    }

    template <typename T>
    vector<T>::~vector(){
      delete [] data_;
    }


    template <typename T>
    void vector<T>::push_back(T val){
      if(size_ <= capacity_){
        data_[size_++] = val;
      }else{
        T* new_data = new T[2 * capacity_];
        copy(data_, data_ + size_, new_data);
        swap(data_, new_data);
        capacity_ = 2 * capacity_;
        data_[size_++] = val;
      }  
    }

    template <typename T>
    T& vector<T>::operator[](size_t val){
      if(val >= 0 && val < size_){
        return data_[val];
      }else{
        throw range_error("whoops");
      }
    }

    template <typename T>
    T& vector<T>::front(){
      return data_[0];
    }

    template <typename T>
    T& vector<T>::back(){
      if(size_ == 0){
        throw range_error("houston, we have a problem");
      }else{
        return data_[size_ - 1];
      }
      
    }

    template <typename T>
    vector<T>& vector<T>::operator=(vector &v){
      capacity_ = v.capacity_;
      size_ = v.size_;
      for(int i=0; i < v.size_; i++){
          push_back(v[i]);
      }

      return *this;
    }

}



#endif

