#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

void arr_to_heap(vector<int>& arr, int n);
void min_heapify(vector<int>& arr, int n, int parent);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, item;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    arr_to_heap(arr, n);

    // print the heapified array
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    

    return 0;
}

void min_heapify(vector<int>& arr, int n, int parent){
    
    int smallest = parent; // initialize the smallest to parent
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    // get the smallest from parent, left, right
    if(left < n && arr[left] < arr[smallest]){
        smallest = left;
    }if(right < n && arr[right] < arr[smallest]){
        smallest = right;
    }

    // if the smallest is not parent, swap it (change the value)
    if(smallest != parent){
        swap(arr[parent], arr[smallest]);

        // recursively heapify the "subtree"
        min_heapify(arr, n, smallest);
    }
    return;
}
void arr_to_heap(vector<int>& arr, int n){

    // the last parent is at position n / 2 - 1
    int last_parent = n / 2 - 1;

    // for every parent from the last parent
    for(int i = last_parent; i >= 0; i--){
        min_heapify(arr, n, i);
    }
    return;
}


