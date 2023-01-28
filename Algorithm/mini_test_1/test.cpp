#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

void arr_to_heap(vector<int>& arr, int n);
void max_heapify(vector<int>& arr, int n, int parent);
void heapSort(vector<int>& arr, int n);

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
    }cout << endl;

    heapSort(arr, n);
    
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}

void max_heapify(vector<int>& arr, int n, int parent){
    
    int largetst = parent; // initialize the smallest to parent
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    // get the smallest from parent, left, right
    if(left < n && arr[left] > arr[largetst]){
        largetst = left;
    }if(right < n && arr[right] > arr[largetst]){
        largetst = right;
    }

    // if the smallest is not parent, swap it (change the value)
    if(largetst != parent){
        swap(arr[parent], arr[largetst]);

        // recursively heapify the "subtree"
        max_heapify(arr, n, largetst);
    }
    return;
}
void arr_to_heap(vector<int>& arr, int n){

    // the last parent is at position n / 2 - 1
    int last_parent = n / 2 - 1;

    // for every parent from the last parent
    for(int i = last_parent; i >= 0; i--){
        max_heapify(arr, n, i);
    }
    return;
}
void heapSort(vector<int>& arr, int n)
{
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        max_heapify(arr, i, 0);
    }
}


