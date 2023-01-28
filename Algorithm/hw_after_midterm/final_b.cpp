#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <iterator>
using namespace std;

map<int, list<int> > GRAPH;
int n, m, k;

void dfs(vector<bool>& visited, int src, map<int, list<int> >& graph){

    visited[src] = true;

    list<int>::iterator i;
    for(i = graph[src].begin(); i != graph[src].end(); i++){
        if(!visited[*i]){
            dfs(visited, *i, graph);
        }
    }
}

int src, des;
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    cin >> src >> des;
    vector< vector<int> >route(m, vector<int>(2, 0));
    set <int> dontgo;
    for(int i  = 0; i < m; i++){
        cin >> route[i][0] >> route[i][1];
    }
    for(int i = 0; i < k; i++){
        int a;
        cin >> a;
        dontgo.insert(a);
    }
    for(int i = 0; i < m; i++){
        if(dontgo.find(route[i][0]) != dontgo.end() || dontgo.find(route[i][1]) != dontgo.end()){
            route[i][0] = route[i][1] = 0;
        }
    }

    for(int i = 0; i < m; i++){
        if(route[i][0] != 0){
            GRAPH[route[i][0]].push_back(route[i][1]);
        }
    }

    // go! and visit

    // step1: all vertice unvisited
    map<int, list<int> >::iterator it;
    vector<bool> visited(n+1, 0);
    dfs(visited, src, GRAPH);
    
    if(visited[des]){
        cout << "SAFE";
    }else{
        cout << "UNSAFE";
    }

    return 0;
}