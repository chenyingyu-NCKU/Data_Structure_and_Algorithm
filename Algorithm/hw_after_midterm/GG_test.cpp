#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <iterator>
using namespace std;
int n , m;
vector<int> vec[200005];
vector<int> dfn(200005, -1), low(200005, -1);
vector<int> parent(200005,-1) ;
vector<long long> cut(200005, 1);
//int child = 0;
int t = 1;

void dfs(int u) {
        dfn[u] = low[u] = t++;
        int child = 0;
        for(int i = 0 ; i < vec[u].size() ; i++){
            // not visited
            if(dfn[vec[u][i]] == -1){
                child ++;
                parent[vec[u][i]] = u;
                dfs(vec[u][i]);
                low[u] = min(low[u],low[vec[u][i]]);

                // when root has several children
                if(parent[u] == -1 && child > 1){
                    cut[u]++;
                }
                // dfn[u] > low[unvisited_neighbor]: we have the same root => strong connected
                if(parent[u] != -1 && low[vec[u][i]] >= dfn[u]){
                    cut[u]++;  
                }
                
            }
            // visited, but it's not my parent: strong connected
            else if(vec[u][i] != parent[u])
                low[u] = min(low[u] , dfn[vec[u][i]]);
        }        
    }


bool cmp( pair<int,long long> a, pair<int,long long> b){
    if (a.second== b.second)
        return a.first < b.first;
    return a.second > b.second;
}

void sol(){
    cin >> n >> m;
    while(true){
        int u , v;
        cin >> u >> v;
        if(u == -1 && v == -1)
            break;
        vec[u].push_back(v);
        vec[v].push_back(u);
    } 
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            dfs(i); 
        }
    }
    vector< pair<int,long long> > block;
    for(int i = 0 ; i < n ; i++){
        block.push_back( pair<int,long long>(i,cut[i]) );
    }
    sort(block.begin() , block.end() , cmp);
    for(int i = 0 ; i < m  ; i++){
        cout << block[i].first << " " << block[i].second << "\n";
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sol();

    for(int i = 0;i <n;i++){
        cout << cut[i] << " ";
    }
    return 0;
}