#include <iostream>
#include "big-O.h"
using namespace std;




int main(){

  int arr[6] = {-1,12,-3,14,-4,3};
  int a[6] = {2,-3,5,-1,0,7};

  cout << "The max value is: " << algoA(arr,6) << endl;
  cout << "The max value is: " << algoB(arr,6) << endl;
  cout << "The max value is: " <<  algoC(arr,6) << endl;


}
