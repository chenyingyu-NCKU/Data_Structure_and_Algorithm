#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right);
long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right);

// IMPORTANT: all the count has to be long long => count can be VERY BIG.
// Time Complexity: O(nlogn)
// in merge sort, we firstly break the array apart
// then merge them <= this is when we count our inv_count

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long ans = 0;
    cin >> n;
    vector<int> arr(n,0);
    vector<int> temp(n,0);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    // n = arr.size();
    ans = mergeSort(arr, temp, 0, n-1);
    ans = ans % 524287;
    cout << ans;

    return 0;
}

long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right){

    int mid;
    long long inv_count = 0;
    // control when we stop
    if(right > left){
        mid = (left + right)/ 2;

        // recursion for left and right parts
        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);

        // merge the left and right subarrays
        inv_count += merge_and_count(arr, temp, left, mid + 1, right);
    }
    return inv_count % 524287;
}
long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right){

    int l = left, r = mid; // point to the first element of left and right subarray
    int k = left; // pointer for the new array temp (the merged array)
    long long count = 0;

    // while there are still elements to compare
    while((l <= mid - 1) && (r <= right)){
        if(arr[l] <= arr[r]){
            temp[k] = arr[l]; // put l to the merged arr
            k++; l++;
        }else{
            temp[k] = arr[r]; // put r to the merged arr
            k++; r++;

            // that means r is small than " all the elements in the right side of the left subarray "
            // count it into inv_count
            count += (mid - l); // " all the elements in the right side of the left subarray "
        }
    }

    // clean the leftover subarray
    while(l <= mid - 1){
        temp[k] = arr[l];
        k++; l++;
    }while(r <= right){
        temp[k] = arr[r];
        k++; r++;
    }
    // copy temp to arr
    for(int i = left; i <= right; i++){
        arr[i] = temp[i];
    }
    return count;
}

