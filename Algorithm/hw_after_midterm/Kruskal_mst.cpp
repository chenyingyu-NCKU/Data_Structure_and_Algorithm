#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <list>
#include <string>
#include <queue>
#include <set>
using namespace std;

int findParent(int x); // check x's set
void merge(int x, int y); // merge the disjoint
long long int Kruskal_mst(); // calculate the shortest path

int parent[2000] = {0}; // used to merge
int node[2000] = {0}; //  used to record node
vector<string> str;
typedef pair<int, int> pr;
vector<pair<int, pr> > edge; // diff, its num
int N, E;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> str;

    cin >> N;
    E = N*(N-1)/2;
    string s;
    for(int i = 0; i < N; i++){
        cin >> s;
        str.push_back(s);
        parent[i] = i; // initialize parent

        // make edges
        for(int j = 0; j < i; j++){
            int weight = 0;
            for(int k = 0; k < str[j].length(); k++){
				if(s[k] != str[j][k]) 
                    weight++;
			}
			edge.push_back(pair<int, pr>(weight, pr(j,i)));
        }
    }cin >> s;

    sort(edge.begin(), edge.end());

    int res = Kruskal_mst();
	cout << "The highest possible quality is 1/" << res << ".";
	return 0;
}
long long int Kruskal_mst(){

    long long int sum = 0;
    int node = 1;
    // go through all the edges
    for(int k = 0; k < E; k++){
        int a = findParent(edge[k].second.first); // v
        int b = findParent(edge[k].second.second); // u
        if(a != b){ // no cycle
            sum += edge[k].first;
            node++;
            merge(a, b);
        }
        if(node == N) break;
    }
    return sum;
}

int findParent(int x){ // find x's set
	if(x != parent[x])
		parent[x] = findParent(parent[x]);
	return parent[x]; 
}
void merge(int x, int y){ 
	if(node[x] > node[y]) parent[y] = x; // make two sets to one
	else parent[x] = y;
	
	if(node[x] == node[y]) node[y]++; //record the node has merge the another
}