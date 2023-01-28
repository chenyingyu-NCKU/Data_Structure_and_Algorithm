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

long long N, M, F;
#define INF __LONG_LONG_MAX__

// A function to print the solution matrix
void printSolution(vector< vector<long long> >& dist);

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(vector< vector<long long> >& graph)
{
	vector< vector<long long> >dist(N, vector<long long>(N));
    long long i, j, k;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			dist[i][j] = graph[i][j];

	for (k = 0; k < N; k++) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])
					&& (dist[k][j] != INF
						&& dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(dist);
}
vector<int> f;
/* A utility function to print solution */
void printSolution(vector< vector<long long> >& dist)
{
    for(long long i = 0; i < N; i++){
        long long int s = INF;

        for(long long k:f){
            if(k == i){
                s = 0; break;
            }

            if(dist[i][k] < s){
                s = dist[i][k];
            }
        }
        if(s == INF) cout << -1 << " ";
        else cout << s << " ";
    }
}

// Driver code
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> F;
	vector< vector<long long> >graph(N, vector<long long>(N, INF));

    for(long long  i = 0; i < M; i++){
        long long a, b, c;
        cin >> a >> b >> c;
        graph[a-1][b-1] = graph[b-1][a-1] = c;
    }

    for(long long  i = 0; i < F; i++){
        long long  a;
        cin >> a;
        f.push_back(a-1);
    }

	// Print the solution
	floydWarshall(graph);
	return 0;
}

