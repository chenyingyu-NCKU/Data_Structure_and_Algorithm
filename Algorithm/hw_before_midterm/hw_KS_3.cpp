#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

// dynamic programming: knapsack problem

int n, W;
int knapSack(vector<int>& cost, vector<int>& val, vector<int>& limit);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector< pair<int, pair<int, int> > > job(n);

    W = 0;
    int latest = 0;
    int score, dl, time;
    for(int i = 0; i < n; i++){
        cin >> score >> dl >> time;
        job[i].first = dl;
        job[i].second.first = score;
        job[i].second.second = time;

        latest = max(latest, dl);
    }
    sort(job.begin(), job.end());

    W = latest;
    // to get the largest volume
    vector<int> val(n);
    vector<int> deadline(n);
    vector<int> cost(n);

    for(int i = 0; i < n; i++){
        deadline[i] = job[i].first;
        val[i] = job[i].second.first;
        cost[i] = job[i].second.second;
    }
    job.clear();

    int max_val = knapSack(cost, val, deadline);
    cout << max_val;

    return 0;
}
int knapSack(vector<int>& cost, vector<int>& val, vector<int>& limit){
    
    vector< vector<int> > KS(2, vector<int>(W + 1));
  
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
         
            if (i == 0 || w == 0){
                KS[i % 2][w] = 0;
            }
            else if (cost[i - 1] <= w){
                KS[i % 2][w] = max( KS[(i - 1) % 2][w] , val[i - 1] + KS[(i - 1) % 2][w - cost[i - 1]]);

                // if w exceed the deadline just take [i][w-1]
                if(w > limit[i - 1]){
                    KS[i % 2][w] = KS[i % 2][w - 1];
                }
            }
            else{
                KS[i % 2][w] = KS[(i - 1) % 2][w];
            }
        }
    }

    return KS[n % 2][W];
}

