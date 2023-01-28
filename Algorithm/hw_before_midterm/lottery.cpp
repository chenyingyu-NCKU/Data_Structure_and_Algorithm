#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
#define LOTTERY_SIZE 6
vector<string> ans;
void all_Combination(vector<int>& arr, vector<int>& sub, int start, int end, int index);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> subarr(LOTTERY_SIZE);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    all_Combination(arr, subarr, 0, n-1, 0);
    // for(int i = 0; i < ans.size(); i++){
    //     cout << ans[i] << endl;
    // }

    return 0;
}
void all_Combination(vector<int>& arr, vector<int>& sub, int start, int end, int index){

    // index is the pointer in the subarray
    // start and end -> arr
    if(index == LOTTERY_SIZE){

        // store the answer
        string temp;
        for(int i = 0; i < LOTTERY_SIZE; i++){
            // temp += to_string(sub[i]) + " ";
            cout << sub[i] << " ";
        }
        // ans.push_back(temp);
        cout << endl;
    }

    for(int i = start; i <= end && (end - i + 1 >= LOTTERY_SIZE - index); i++){
        sub[index] = arr[i];
        all_Combination(arr, sub, i+1, end, index+1);
    }
}
