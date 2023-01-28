#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <cstdlib> // abs
#include <climits>
using namespace std;

// This problem is mainly an extension to the Dynamic Programming (Partition Problem). 
// minimun subset difference

int N;
int findMin_diff_dp(vector<int>& num);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> num(N);

    for(int i = 0; i < N; i++){
        cin >> num[i];
    }

    int min_diff = findMin_diff_dp(num);
    cout << min_diff;

    return 0;
}
int findMin_diff_dp(vector<int>& num){

    int SUM = 0;
    for(int i = 0; i < N; i++){
        SUM += num[i];
    }

    vector< vector<bool> >dp(N, vector<bool>(SUM + 1, 0));
    // dp[4][10]:
    // is there an arrangement of the first 4 numbers, which sum to 10

    for(int i = 0; i < N; i++){
        dp[i][0] = 1;
    }

    for(int j = 1; j < SUM + 1; j++){
        dp[0][j] = 0;
    }

    for(int i = 1; i < N; i++){
        for(int j = 1; j < SUM + 1; j++){
            if(j - num[i-1] > -1){
                dp[i][j] = (dp[i-1][j - num[i-1]] | dp[i-1][j]);
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    int diff = INT_MAX;
    for(int j = 0; j < SUM + 1; j++){
        if(dp[N-1][j] == true){
            int sum1 = j;
            int sum2 = SUM - sum1;
            diff = min( diff, abs(sum1 - sum2));
        }
    }
    return diff;
}

