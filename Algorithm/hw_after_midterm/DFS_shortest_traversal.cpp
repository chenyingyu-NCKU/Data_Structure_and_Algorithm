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
bool dfs(map<int, list<int> >& adj,int src, int path);

map<int, list<int> > adj;
vector<bool> mustPass(200010, 0);
vector<bool> visited(200010, 0);
vector<bool> noNeedToVisit(200010, 0);

int head = 0; // will be initialize to one of the mustPass
int path_edge = 0;
int longest_conti_path = 0;


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    

    for(int i = 0; i < N-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i = 0; i < M; i++){
        int c;
        cin >> c;
        mustPass[c] = true;
        head = c; // start with one of the mustPass
    }

    dfs(adj, head, 0); // find the "start point" of the logest continuous path

    int temp = head;
    // check again
    longest_conti_path = 0;
    path_edge = 0;
    fill(visited.begin(), visited.end(), 0);

    dfs(adj, head, 0); // check the smallest start point
    head = min(head, temp);

    cout << head << endl;
    long long int edges = (long long)path_edge*2 - longest_conti_path;
    cout << edges*1000 + (long long)M*870000;


    return 0;
}

// difine whether we have to pass this node
// return true 1. this is a mustPass 2. there's a mustPass behind
bool dfs(map<int, list<int> >& adj,int src, int path){

    bool needToVis = false; // need to pass this node
    visited[src] = true;

    if(mustPass[src]){
        if(path > longest_conti_path){
        // do not turn back, find the longest conti path
            head = src;
            longest_conti_path = path;
        }
        else if(path == longest_conti_path){
            head = min(head, src);
        }
        needToVis = true;
    }

    // go through each adj
    list<int>::iterator it;
    for(it = adj[src].begin(); it!= adj[src].end(); it++){
        int neigh = *it;
        if(!visited[neigh] && !noNeedToVisit[neigh]){

            if(dfs(adj, neigh, path + 1)){ // if there's a must-go behind
                needToVis = true;
                path_edge++; // the edge we ahve pass (including turn back)

            }
            else{
                noNeedToVisit[neigh] = true;
            }
        }
    }
    return needToVis;
}

