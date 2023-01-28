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

int N, M;
vector< vector<int> > adj; // graph 2D (E, 2)
int node_connectedComponents(int src);
int num_of_connectedComponents(vector< vector<int> >& adj2);

// Number of Connected Components in an Undirected Graph
// Union Find (Disjoint Set): 
// performance operation on "non-overlapping" "disjoint" "subset"

bool mycompare(vector<int>& a, vector<int>& b){
    if(a[1] != b[1]){
        return a[1] > b[1];
    }else{
        return a[0] < b[0];
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    int u = 0, v = 0;

    while(1){
        cin >> u >> v;

        if(u == -1 && v == -1) break;

        vector<int> temp(2);
        temp[0] = u; temp[1] = v;
        adj.push_back(temp);
    }
    // now we have a graph


    vector< vector<int> >ans;
    for(int i = 0; i < N; i++){
        vector<int> temp(2);
        temp[0] = i; 
        temp[1] = node_connectedComponents(i);
        ans.push_back(temp);
    }

    // sort with the connected components
    sort(ans.begin(), ans.end(), mycompare);

    for(int i = 0; i < M; i++){
        cout << ans[i][0] << " "<< ans[i][1] << endl;
    }

    return 0;
}

int node_connectedComponents(int src){

    vector< vector<int> > adj2; // remove src

    for(int i = 0; i < adj.size(); i++){
        if(adj[i][0] != src && adj[i][1]!= src){
            adj2.push_back(adj[i]);
        }
    }

    int components_without_src = num_of_connectedComponents(adj2) - 1;
    // -1 : because "src itself" is also a component

    return components_without_src;
}


int merge(vector<int>& parent, int v){

    if(parent[v] == v){
        return v;
    }else{
        return merge(parent, parent[v]);
    }
}

// Union Find (Disjoint Set)
int num_of_connectedComponents(vector< vector<int> >& adj2){

    vector<int> parent(N);
    for(int i = 0; i < N; i++){
        parent[i] = i;
    }

    // merge subset
    for(int i = 0; i < adj2.size(); i++){
        parent[ merge(parent, adj2[i][0]) ] = merge(parent, adj2[i][1]);
    }

    int ans = 0;
    for(int i = 0; i < N; i++){
        if(parent[i] == i){
            ans++;
        }
    }
    return ans;
}