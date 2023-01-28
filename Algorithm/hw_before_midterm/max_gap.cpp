#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int maximumGap(vector<int>& arr);
int n;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n; 
    vector<int> arr(n);
    int ans = 0;

    // input array
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    if(n < 2){
        ans = 0;
    }else{
        ans = maximumGap(arr);
    }
    cout << ans;
    
    return 0;
}
int maximumGap(vector<int>& arr){

    int max_gap = 0;
    sort(arr.begin(), arr.end());
    for(int i = 1; i < arr.size(); i++){
        if(arr[i] - arr[i-1] > max_gap){
            max_gap = arr[i] - arr[i-1];
        }
    }
    return max_gap;
}
