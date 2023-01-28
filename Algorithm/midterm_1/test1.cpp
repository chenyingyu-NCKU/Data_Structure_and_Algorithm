#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int N;

long fib(int n){
   long arr[n];

   arr[0] = 1;
   arr[1] = 2;

   for(int i = 2; i < n; i++){
      arr[i] = arr[i-1] + arr[i-2];
   }
   return arr[n-1];
}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    cout << fib(N);
    
    return 0;
}