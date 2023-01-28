#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

#define INFINITE 100000

void dijkstra();

int GetNearest();

int V, root;    // V: number of vertex, root: root of tree
int dist[1000000]; // the shortest distance from root to the node
int parent[1000000]; // the last node (with dist[])
bool visited[1000000]; // if we have reached this node


int main(){

    // enter the file the user want to load in
    string file = "";
    cout << "Please input the file name: ";
    cin >> file;

    //load in the file.txt by using ifstream
    ifstream inFile;
    inFile.open(file);

    // create a output file
    string outfile_name;
    outfile_name.assign(file, 2, file.length()-2);
    outfile_name = "out" + outfile_name;
    ofstream outFile(outfile_name);

    // MAKE SURE we successfully load the file
    if(inFile.is_open()){
        // get "V"
        string firstline = "";
        getline(inFile,firstline);
        V = stoi(firstline);
    }

    // create the cost(weight) 
    int cost[V][V];
    // initialize
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(i == j){
                cost[i][j] = 0;
                // route to itself
            }else{
                cost[i][j] = INFINITE;
                // initialize to infinte
            }
        }
    }

    string line = "";
    // get the edges
    // BE CAREFUL: input 1~V, but we want 0~V-1
    for(int i = 0; i < V-1; i++){
        int v, u, w;
        // get u, v, w
        getline(inFile, line);
        stringstream sstream(line);
        string item;
        int a = 0;
        while(getline(sstream, item, ' ')){
            if(a == 0){
                v = stoi(item) - 1;
            }else if(a == 1){
                u = stoi(item) -1;
            }else if(a == 2){
                w = stoi(item);
            }
            a++;
        }
        cost[v][u] = cost[u][v] = w;
    }

    getline(inFile, line);
    root = stoi(line) - 1;

    
    /************* Dijkstra's Algorithm *************/
    // 1. select the unvisited node with the best path from root,
    //    put it into dist[]
    // 2. calculate the path from the node we just add (curr) to its nearest node,
    //    (the unvisited)
    //    if curr + (curr to nearset) < nearset
    //    update dist[] and parent[]
    // 3. repeat step 2

    // initialize
    for(int i = 0; i < V; i++){
        dist[i] = INFINITE;
        parent[i] = i;
    }
    dist[root] = 0;

    for(int i = 0; i < V; i++){
        int nearest = GetNearest();
        visited[nearest] = true;

        for(int adj = 0; adj < V; adj++){
            if(cost[nearest][adj] != INFINITE && dist[adj] > dist[nearest] + cost[nearest][adj]){
            // if they are connected && step 2
                dist[adj] = dist[nearest] + cost[nearest][adj];
                parent[adj] = nearest;
                // update dist[] and parent[]
            }
        }
    }
    
    // output
    for(int i = 0; i < V; i++){
        outFile << i+1 << " " << dist[i] << endl;
    }

    return 0;
}

// step 1
int GetNearest(){
    int minValue = INFINITE;
    int minNode = 0;
    for(int i = 0; i < V; i++){
        if(!visited[i] && dist[i] < minValue){
            minValue = dist[i];
            minNode = i;
        }
    }
    return minNode;
}



