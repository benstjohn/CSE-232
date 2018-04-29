#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
#include<string>
using std::to_string; using std::string; using std::sqrt;

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
  return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

// YOUR FUNCTIONS HERE
long gcd(long a, long b){
    while(b != 0){
      long t = b;
      b = a % b;
      a = t;
    }
    return a;
}

long divisor_sum(long numCalc){
  long totalSum = numCalc;

  for(int i = 2; i <= sqrt(numCalc); i++){
    if(numCalc % i == 0){
      if(i==(numCalc/i)){
        totalSum = totalSum + i;
      }else{
        totalSum = totalSum + (i + numCalc/i);
      }
    }
  }

  return totalSum + 1;
}

bool is_solitary(long n){
  long divSum = divisor_sum(n);
  if(gcd(divSum, n) == 1){
    return true;
  }else{
    return false;
  }

}

string friendly_check(long checkNum, long upperLimit){
  long ab_numerator = divisor_sum(checkNum);
  long gcdVal = gcd(ab_numerator, checkNum);
  ab_numerator = ab_numerator/gcdVal;
  long ab_denominator = checkNum/gcdVal;

  
  long temp_num = 0;
  long friendly = -1;
  long temp_denom = 0;
  
  for(int i = 2; i <= upperLimit; i++){
   temp_num = divisor_sum(i);
   long temp_gcd = gcd(temp_num, i);
   temp_num = temp_num/temp_gcd;
   temp_denom = i/temp_gcd;
   
   if(i != checkNum && temp_num == ab_numerator && temp_denom == ab_denominator){
     friendly = i;
     break;
   }
  }

    return abIndex_friend(ab_numerator, ab_denominator, friendly);
}




int main (){
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  switch (test) {
  case 1 : {   // divisor sum test
    long input;
    cin >> input;
    cout << divisor_sum(input) << endl;
    break;
  } // of case 1

  case 2:{    // gcd test
    long first, second;
    cin >> first >> second;
    cout << gcd(first, second) << endl;
    break;
  } // of case 2

  case 3: {    // is_solitary test
    long input;
    cin >> input;
    cout << is_solitary(input) << endl;
    break;
  } // of case 3

  case 4: {
    // friend check. Make sure the return value is the
    // result of calling abIndex_friend, a string!
    long input, limit;
    cin >> input >> limit;
    cout << friendly_check(input, limit) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main
