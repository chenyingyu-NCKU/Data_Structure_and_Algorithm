#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <queue>
#include <cstdlib> // use abs
using namespace std;

#define INFINITE INT_MAX
#define MAX_N 600005
int N, M, C;
int dist[MAX_N]; // the shortest distance from root to the node
int parent[MAX_N]; // the last node (with dist[])
bool visited[MAX_N]; // if we have reached this node
int root = 0;

int GetNearest();
void dijkstra(vector< vector<int> >& cost);


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> C;
    vector<int> floor(N); // floor[0] = 3; room0 is at floor 3
    for(int i = 0; i < N; i++){
        int f;
        cin >> f;
        floor[i] = f;
    }

    vector< vector<int> > cost(N, vector<int>(N, 0)); // adj[u][v] = cost
    for(int i = 1; i < N; i++){
        for(int j = 0; j < i; j++){
            if(floor[i] == floor[j]){
                cost[i][j] = cost[j][i] = INFINITE;
            }
            else{
                cost[i][j] = cost[j][i] = C * abs(floor[i]-floor[j]);
            }
        }
    }

    for(int i = 0; i < M; i++){
        int a ,b, w;
        cin >> a >> b >> w;
        a--; b--;

        if(cost[a][b] > w){
            cost[a][b] = cost[b][a] = w;
        }
    }

    dijkstra(cost);
    if(dist[N-1] == INFINITE) cout << -1;
    else cout << dist[N-1];

    return 0;
}

void dijkstra(vector< vector<int> >& cost){

    /************* Dijkstra's Algorithm *************/
    // 1. select the unvisited node with the best path from root,
    //    put it into dist[]
    // 2. calculate the path from the node we just add (curr) to its nearest node,
    //    (the unvisited)
    //    if curr + (curr to nearset) < nearset
    //    update dist[] and parent[]
    // 3. repeat step 2

    // initialize
    for(int i = 0; i < N; i++){
        dist[i] = INFINITE;
        parent[i] = i;
    }
    dist[root] = 0;

    for(int i = 0; i < N; i++){
        int nearest = GetNearest();
        visited[nearest] = true;

        for(int adj = 0; adj < N; adj++){
            if(cost[nearest][adj] != INFINITE && dist[adj] > dist[nearest] + cost[nearest][adj]){
            // if they are connected && step 2
                dist[adj] = dist[nearest] + cost[nearest][adj];
                parent[adj] = nearest;
                // update dist[] and parent[]
            }
        }
    }
}

// step 1
int GetNearest(){
    int minValue = INFINITE;
    int minNode = 0;
    for(int i = 0; i < N; i++){
        if(!visited[i] && dist[i] < minValue){
            minValue = dist[i];
            minNode = i;
        }
    }
    return minNode;
}
