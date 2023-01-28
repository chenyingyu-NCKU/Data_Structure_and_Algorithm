#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <iterator>
#include <map>
using namespace std;

// Tarjan Algorithm

int N, M;
int MAX_SIZE = 200010;

map<int, list<int> > adj; // graph
vector<int> parent(MAX_SIZE, -1);
vector<int> cut(MAX_SIZE, 1); 
vector<int> dfn(MAX_SIZE, -1), low(MAX_SIZE, -1);
int depth = 1;
// cut = 1, child = 0, parent = -1

void dfs_tarjan(int u){
    dfn[u] = low[u] = depth;
    depth++;
    int child = 0;

    list<int>::iterator it;
    for(it = adj[u].begin(); it != adj[u].end(); it++){
        // neighbor is unvisited
        if(dfn[*it] == -1){
            parent[*it] = u;
            child++;

            dfs_tarjan(*it);
            low[u] = min(low[u], low[*it]); // define low

            // when root has several children
            if(parent[u] == -1 && child > 1){
                cut[u]++;
            }
            // dfn[u] > low[unvisited_neighbor]: we have the same root => strong connected (same component)
            if(parent[u] != -1 && dfn[u] <= low[*it]){
                // the next one is not strong connected
                cut[u]++;
            }

        }
        // visited, but it's not my parent: strong connected
        else if((*it) != parent[u]){
            low[u] = min(low[u], dfn[*it]);
        }
    }
}

bool my_compare(vector<int>& a, vector<int>& b);

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    int u = 0, v = 0;

    while(1){
        cin >> u >> v;

        if(u == -1 && v == -1) break;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // now we have a graph, start visit "Tarjan"
    for(int i = 0; i < N; i++){
        if(dfn[i] == -1) // if unvisited
            dfs_tarjan(i);
    }

    // finish, print ans (sort)
    vector< vector<int> >ans;
    for(int i = 0; i < N; i++){
        vector<int> temp(2);
        temp[0] = i; temp[1] = cut[i];
        ans.push_back(temp);
    }

    sort(ans.begin(), ans.end(), my_compare);
    for(int i = 0; i < M; i++){
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}

bool my_compare(vector<int>& a, vector<int>& b){
    if(a[1] == b[1])
        return a[0] < b[0];
    return a[1] > b[1];
}