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
#define int long long
#define vi vector<int>
#define INF (int)1e17+5

typedef pair<int, int> pr;

long long  gcd(long long  x, long long  y) {
    return y == 0 ? x : gcd(y, x % y);
}

vector< vector< pr > > v;
void solution(){
    int N, M, F;
    cin >> N >> M >> F ;
    v.resize(N+1,vector< pr >());
    vi d(N+1, INF);
    vi visited(N+1, 0);
    priority_queue< pr ,vector<pr>,greater<pr> > q;
    for(int i=0;i<M;i++){
        int x,y,z;
        cin >> x >> y >> z;
        v[x].push_back(make_pair(z,y));
        v[y].push_back(make_pair(z,x));
    }
    for(int i=0;i<F;i++){
        int x;
        cin >> x;
        v[0].push_back(make_pair(0,x));
        d[x]=0;
    }
    q.push(make_pair(0,0));
    d[0] = 0;
    while(!q.empty()){
        pr x = q.top();
        q.pop();
        if(visited[x.second]){
            continue;
        }
        visited[x.second] = 1;
        for(int i=0;i<v[x.second].size();i++){
            if(!visited[v[x.second][i].second]){
                // if(d[v[x.second][i].second]>=v[x.second][i].first+d[x.second]){
                d[v[x.second][i].second] = min(d[v[x.second][i].second],v[x.second][i].first+d[x.second]);
                // d[v[x.second][i].second] = v[x.second][i].first+d[x.second];
                q.push(make_pair(d[v[x.second][i].second],v[x.second][i].second));
                // }
            }
        }

    }
    for(int i=1;i<N+1;i++){
        if(d[i]==INF){
            cout<<-1<<' ';
        }
        else
            cout<<d[i]<<' ';
    }

}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    // multiply
    solution();
    return 0;
}