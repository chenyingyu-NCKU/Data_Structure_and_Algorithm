#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <map>
#include <functional>   // std::greater
#include <queue>
using namespace std;

#define INF 1000
int N, M;
void sol();

bool mycompare(pair<int, int>& a, pair<int, int>& b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin >> N >> M){
        sol();
    }

    return 0;
}

void sol(){

    priority_queue<int, vector<int>, greater<int> > Q;
    vector<int> smaller_num(N+1, 0);
    vector< vector<int> > greater(N+1);

    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        greater[a].push_back(b);
        smaller_num[b]++;
    }

    for(int i = 1; i <= N; i++){
        if(smaller_num[i] == 0){
            Q.push(i);  // no one is samller than i, ready to be print
        }
    }

    while (!Q.empty())
    {
        int out = Q.top();
        cout << out << " ";
        Q.pop();

        for(int i : greater[out]){
            smaller_num[i]--;
            if(smaller_num[i] == 0){
                Q.push(i);
            }
        }
    }cout << endl;

    return;
}
