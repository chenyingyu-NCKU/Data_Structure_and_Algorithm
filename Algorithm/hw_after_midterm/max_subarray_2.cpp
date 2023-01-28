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
int maxTwoSubArrays(vector<int>& arr, int size);

// we will use "Kadane's Algorithm" to find the maximum subarray

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int max_two_sub = maxTwoSubArrays(arr, n);
    cout << max_two_sub;

    return 0;
}

int maxTwoSubArrays(vector<int>& arr, int size){
    // we have left[] and right[]
    // left[i] means the max of arr[0...i]; right[i] means the max of arr[i...n-1]

    // 1. find the left[] and right[] by Kadane
    // 2. compare each left[i] right[i], the largest is the ans

    // 用 Kadane's Algorithm 要注意初始化问题
    //（从头到尾循环，必须要以 nums[0] 做初始化，从 index = 1 开始搜；
    // 或者从尾到头循环则以nums[n-1]初始化，从index = n - 2开始)

    vector<int> left(n, arr[0]);
    vector<int> right(n, arr[n-1]);

    int pre_max = left[0];
    int cur_max = left[0];
    // loop from left to right
    for(int i = 1; i < n; i++){
        pre_max = max(arr[i], pre_max + arr[i]);
        cur_max = max(cur_max, pre_max);
        left[i] = cur_max;
    }

    pre_max = right[n-1];
    cur_max = right[n-1];
    // loop from right to left
    for(int i = n-2; i >= 0; i--){
        pre_max = max(arr[i], pre_max + arr[i]);
        cur_max = max(cur_max, pre_max);
        right[i] = cur_max;
    }

    int ans = INT_MIN;
    for(int i = 0; i < n-1; i++){
        ans = max(ans, left[i] + right[i+1]);
    }

    return ans;
}

