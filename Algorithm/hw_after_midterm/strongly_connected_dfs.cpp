#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <map>
#include <iterator>
using namespace std;

int N, M;
vector<int> ans;
map<int, list<int> > GRAPH;

bool isStrongConnect();
map<int, list<int> > transposeGraph();
void dfs(vector<bool>& visited, int src, map<int, list<int> >& graph);

// Kosaraju’s DFS

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<bool> ans;

    do{
        cin >> N >> M;

        for(int i = 0; i < M; i++){
            int a, b, c;
            cin >> a >> b >> c;

            if(c == 1){
                GRAPH[a].push_back(b);
            }else if(c == 2){
                GRAPH[a].push_back(b);
                GRAPH[b].push_back(a);
            }
        }

        // now we have a graph (adj)
        if(!GRAPH.empty()){
            ans.push_back(isStrongConnect());
        }
        GRAPH.clear();

    }while(N!=0 || M!=0);

    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
    }

    return 0;
}

// Kosaraju’s DFS
bool isStrongConnect(){

    // step1: all vertice unvisited
    map<int, list<int> >::iterator it;
    vector<bool> visited(N+1, 0);

    // step2: dfs from the first vertex
    dfs(visited, 1, GRAPH);

    // step3: if dfs cannot visit all, return false
    for(int i = 1; i < N+1; i++){
        if(!visited[i]){
            return false;
        }
    }

    // step4: create reverse graph
    map<int, list<int> > trans_g = transposeGraph();

    // mark all unvisites
    for(int i = 1; i < N+1; i++){
        visited[i] = false;
    }

    // srep5: dfs reverse graph with the same start
    dfs(visited, 1, trans_g);

    // step6: if dfs cannot visit all, return false
    for(int i = 1; i < N+1; i++){
        if(!visited[i]){
            return false;
        }
    }

    return true;
}

void dfs(vector<bool>& visited, int src, map<int, list<int> >& graph){

    visited[src] = true;

    list<int>::iterator i;
    for(i = graph[src].begin(); i != graph[src].end(); i++){
        if(!visited[*i]){
            dfs(visited, *i, graph);
        }
    }
}

// create a graph (reverse)
map<int, list<int> > transposeGraph(){
    map<int, list<int> > graph;

    map<int, list<int> >::iterator v;
    list<int>:: iterator i;

    for(v = GRAPH.begin(); v != GRAPH.end(); v++){
        for(i = (*v).second.begin(); i != (*v).second.end(); i++){
            graph[*i].push_back((*v).first);
        }
    }

    return graph;
}


     

        

