#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

// dynamic programming: knapsack problem

int n, W;
int knapSack(vector<int>& wt, vector<int>& val);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> W;
    vector<int> val(n);
    vector<int> weight(n);

    for(int i = 0; i < n; i++){
        cin >> val[i] >> weight[i];
    }

    int max_val = knapSack(weight, val);
    cout << max_val;

    return 0;
}
int knapSack(vector<int>& wt, vector<int>& val){
    
    vector< vector<int> > KS(2, vector<int>(W + 1));
    // We know we are always using the the current row or
    // the previous row of the KS. Thereby we can
    // improve it further by using a 2D array but with only
    // 2 rows i%2 will be giving the index inside the bounds
    // of 2d array K
  
    for (int i = 0; i < n+1; i++) {
        for (int w = 0; w < W+1; w++) {

            if (i == 0 || w == 0){
                KS[i % 2][w] = 0;
            }
            else if (wt[i - 1] <= w){
                KS[i % 2][w] = max( KS[(i - 1) % 2][w] , val[i - 1] + KS[(i - 1) % 2][w - wt[i - 1]]);
            }
            else{
                KS[i % 2][w] = KS[(i - 1) % 2][w];
            }
        }
    }
    return KS[n % 2][W];
}


