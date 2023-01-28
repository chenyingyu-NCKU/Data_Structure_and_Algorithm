#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include<climits>
using namespace std;

int n;
int minRemove(vector<int>& arr, int n);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int min_remove = minRemove(arr, n);
    cout << min_remove;

    return 0;
}

int minRemove(vector<int>& arr, int n){

    vector<int> LIS_left(n, 1);
    vector<int> LIS_right(n, 1);

    // loop from left to right
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(arr[i] > arr[j]){
                LIS_left[i] = max(LIS_left[i], LIS_left[j] + 1);
            }
        }
    }

    // loop from right to left
    for(int i = n-2; i >= 0; i--){
        for(int j = n-1; j > i; j--){
            if(arr[i] > arr[j]){
                LIS_right[i] = max(LIS_right[i], LIS_right[j] + 1);
            }
        }
    }

    // i 高點重疊
    int min_change = INT_MAX;
    for(int i = 0; i < n-1; i++){
        min_change = min(min_change, n - (LIS_left[i] + LIS_right[i]) + 1);
    }

    return min_change;
}
