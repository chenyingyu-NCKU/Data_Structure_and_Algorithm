#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

#define INFINITE INT_MAX
#define MAX_N 1005
int N, M;
long long int dist[MAX_N]; // the shortest distance from root to the node
int parent[MAX_N]; // the last node (with dist[])
bool visited[MAX_N]; // if we have reached this node
int root = 0;

int GetNearest();
void dijkstra(vector< vector<int> >& cost);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    vector< vector<int> > adj(N, vector<int>(N, INFINITE)); // adj[u][v] = cost
    for(int i = 0; i < M; i++){
        int a, b, c;
        cin >> a >> b >> c;
        adj[a-1][b-1] = c;
    }
    // now we have the cost map :)
    dijkstra(adj);

    // now we have the shortest path from root
    long long int longest_one = 0;
    for(int i = 0; i < N; i++){
        if(dist[i] > longest_one){
            longest_one = dist[i];
        }
    }
    cout << longest_one;

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
    long long int minValue = INFINITE;
    int minNode = 0;
    for(int i = 0; i < N; i++){
        if(!visited[i] && dist[i] < minValue){
            minValue = dist[i];
            minNode = i;
        }
    }
    return minNode;
}