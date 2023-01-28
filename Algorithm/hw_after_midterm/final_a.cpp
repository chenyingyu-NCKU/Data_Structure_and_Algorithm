#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <list>
#include <queue>
#include <set>
#include <cstdlib> // use abs
#include <functional>   // std::greater
using namespace std;

// MST use Prim's Algorithm (BFS)
// O(n^2 logn) 
// BFS (priority queue)
// my note: O(n^2) or O(e + nlogn)

int n, m;
typedef pair<int, int> pr;
long long int min_Prim();
map<int , list<pr> > adj; // store all the adj: pair{cost, node}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    int a, b, c;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        adj[a].push_back(pr(c, b));
        adj[b].push_back(pr(c, a));
    }

    // start at random point, we say point[0]
    long long int min_cost = min_Prim();
    cout << min_cost;
    return 0;
}

long long int min_Prim(){

    long long int res = 0;
    set<int> visit;
    priority_queue< pr > minHeap;
    minHeap.push(pr(0, 0)); // {cost, node0}
    while (visit.size() < n)
    {
        int cost = minHeap.top().first;
        int i = minHeap.top().second;
        minHeap.pop();

        if(visit.find(i) == visit.end()){ // unvisit
            res += cost;
            visit.insert(i);

            for(pr nei: adj[i]){
                if(visit.find(nei.second) == visit.end()){ // neighbor unvisit
                    minHeap.push(pr(nei.first, nei.second));
                }
            }
        }
    }
    return res;
}
