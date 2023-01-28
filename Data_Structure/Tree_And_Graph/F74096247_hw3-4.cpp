#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

// Time Complexity: O(E logV)
// Space Complexity: O(E + V)

struct Edge{
    int u;
    int v;
    int weight;
};

int kruskals(Edge * input, int V, int E);

int main(){

    int V, E; // how many datasets

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
        // get "V" and "E" (vertex and edge)
        string firstline = "";
        getline(inFile,firstline);
        // split the string with space
        stringstream firststream(firstline);
        string item;
        int a = 0;
        while(getline(firststream, item, ' ')){
            if(a == 0){
                V = stoi(item);
            }else if(a == 1){
                E = stoi(item);
            }
            a++;
        }
    }

    /************* Kruskal's Algorithm *************/
    // 1. sort all the edges in increasing order of their weight
    // 2. pick the smallest edges 
    //    if it form a circle, ignore it
    //    or we include the egde
    // 3. repeat step 2

    Edge* input  = new Edge[E];

    string line = "";
    for(int i = 0; i < E; i++){
        // get u, v, w
        getline(inFile, line);
        stringstream sstream(line);
        string item;
        int a = 0;
        while(getline(sstream, item, ' ')){
            if(a == 0){
                input[i].u = stoi(item);
            }else if(a == 1){
                input[i].v = stoi(item);
            }else if(a == 2){
                input[i].weight = stoi(item);
            }
            a++;
        }
    }

    int ans = 0;
    ans = kruskals(input, V, E);
    outFile << ans << endl;

    return 0;
}

bool compare(Edge e1, Edge e2){
    return e1.weight < e2.weight;
    // increasing order
}

int findParent(int k, int * parent){
    if(parent[k] == k){
    // the ancester !!
        return k;
    }else{
        // keep finding its parent
        return findParent(parent[k], parent);
    }
}

int kruskals(Edge * input, int V, int E){
    // sort in a increasing order (weight)
    // sort from input to input + E by compare
    sort(input, input + E, compare);

    // mini spanning tree
    Edge* output = new Edge[V-1];

    // to check the vertex parent (check cycle)
    int* parent = new int[V];
    for(int i = 0; i < V; i++){
        parent[i] = i;
    }

    int count = 0;
    int i = 0;
    while(count < V-1){
        Edge current  = input[i];

        // check if we can add current into mini spanning tree (MST)
        int sourceParent = findParent(current.u, parent);
        int destParent = findParent(current.v, parent);
        if(sourceParent != destParent){
            // do not form a circle, add it to output
            output[count] = current;
            count++;
            parent[sourceParent] = destParent; // connect
        }
        i++;
    }

    int sum = 0;
    for(int i = 0; i < V-1; i++){
        sum += output[i].weight;
    }
    return sum;
}
