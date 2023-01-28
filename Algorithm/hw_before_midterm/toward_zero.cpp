#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <cstdlib> // abs
using namespace std;

// This problem is mainly an extension to the Dynamic Programming (Partition Problem). 
// minimun subset difference

int N;
int findMin(vector<int>& arr);
int findMinDifference(vector<int>& arr, int i, int accumalated, int total);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> arr(N);

    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }

    // check one by one, find the min ｜(total - accumulate) - accumulated｜
    int ans = findMin(arr);
    cout << ans;

    return 0;
}

int findMin(vector<int>& arr){
    
    int total = 0;
    for(int i = 0; i < N; i++){
        total += arr[i];
    }

    return findMinDifference(arr, 0, 0, total);
}
int findMinDifference(vector<int>& arr, int i, int accumalated, int total){

    if(i == N){ // stop
        return abs( (total - accumalated) - accumalated);
    }
    
    // include or not_include which is smaller
    return min( findMinDifference(arr, i+1, accumalated + arr[i], total), findMinDifference(arr, i+1, accumalated, total) );
}

//                  BY THE WAY
// we cannot sort the array, and distribute the value to two part
// consider the case {5, 5, 3, 3, 3}
// if we use the way mentioned above, we got
// a = 5 + 3 + 3
// b = 5 + 3 
// difference = 3, but the ans = 1 (10 -9)