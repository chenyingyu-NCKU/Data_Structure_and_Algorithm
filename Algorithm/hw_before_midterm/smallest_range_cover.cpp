#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
using namespace std;

// https://www.youtube.com/watch?v=ejVD92bJe34

vector<int> smallestRange(vector< vector<int> >& arr2D);
int n;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector< vector<int> > arr2D;
    vector<int> ans;
    cin >> n;
    
    // input => 2D array
    for(int i = 0; i < n; i++){
        int m = 0;
        cin >> m;
        vector<int> arr;
        for(int j = 0; j < m; j++){
            int k;
            cin >> k;
            arr.push_back(k);
        }
        arr2D.push_back(arr);
    }

    ans = smallestRange(arr2D);
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < arr2D[i].size(); j++){
    //         cout << arr2D[i][j] << " ";
    //     }cout << endl;
    // }

    return 0;
}

vector<int> smallestRange(vector< vector<int> >& arr2D){
    
    set< pair<int, int> > cur_set; // {value, group}
    // [0, 4, 5] would be the first cur_set => range = [0, 5]

    vector<int> pointer(n, 0); // point to each group
    for(int i = 0; i < n; i++){

        // initialize our set (cur_range)
        pair<int, int> item(arr2D[i][0], i);
        cur_set.insert(item);
    }

    int k = cur_set.begin()->second; // cur_smallest_group
    int smallest_range = 500000;
    vector<int> ans(2);

    // while loop will stop if any of the array(1D) has been finished
    while (pointer[k] != arr2D[k].size())
    {
        // if the big - small in the set is smaller than the smallest_range 
        // renew it
        int range = cur_set.rbegin()->first - cur_set.begin()->first;
        if(range < smallest_range){
            smallest_range = range;
            ans[0] = cur_set.begin()->first;
            ans[1] = cur_set.rbegin()->first;
        }
        k = cur_set.begin()->second;
        pointer[k]++;
        cur_set.erase(cur_set.begin());
        pair<int, int> item(arr2D[k][pointer[k]], k);
        cur_set.insert(item);
    }
    return ans;
}
