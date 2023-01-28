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

int n;
int min_Prim(vector< vector<int> >& point);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector< vector<int> > point(n, vector<int>(2, 0));
    for(int i = 0; i < n; i++){
        cin >> point[i][0] >> point[i][1];
    }

    // start at random point, we say point[0]
    int min_cost = min_Prim(point);
    cout << min_cost;
    return 0;
}

int min_Prim(vector< vector<int> >& point){

    typedef pair<int, int> pr;
    map<int , list<pr> > adj; // store all the adj: pair{cost, node}

    for(int i = 0; i < n; i++){
        int x1 = point[i][0]; int y1 = point[i][1];
        for(int j = i+1; j < n; j++){
            int x2 = point[j][0]; int y2 = point[j][1];
            int dist = abs(x1 - x2) + abs(y1 - y2);
            adj[i].push_back(pr(dist, j));
            adj[j].push_back(pr(dist, i));
        }
    }

    int res = 0;
    set<int> visit;
    priority_queue<pr, vector<pr>, greater<pr> > minHeap;
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
