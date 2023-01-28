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

struct Point
{
    int x;
    int y;
};
struct QPoint
{
    Point pt;
    int dist;
};

// BFS with stander (0,0) // this is a 2D maze map
int ROW, COL;
bool isValid(int row, int col);
int BFS(vector< vector<int> >& mat, Point start, Point end);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> ROW >> COL;

    int sx, sy, ex, ey;
    // Notice node is standered with (1,1)
    cin >> sx >> sy >> ex >> ey;

    // get maze
    vector< vector<int> > maze(ROW, vector<int>(COL));
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j ++){
            cin >> maze[i][j];
        }
    }

    // set sorce and end
    Point source = {sx - 1, sy - 1};
    Point end = {ex - 1, ey - 1};

    int shortest_dist = BFS(maze, source, end);
    cout << shortest_dist;

    return 0;
}

bool isValid(int row, int col){
    // to see if the point is out of bound
    return (row >= 0) && (col >= 0) && (row < ROW) && (col < COL);
}

int rd[] = {-1, 0 ,0, 1}; // row direction
int cd[] = {0, -1, 1, 0}; // global

int BFS(vector< vector<int> >& mat, Point start, Point end){

    if(mat[start.x][start.y] == 0 || mat[end.x][end.y] == 0){
        return -1;
    }

    vector< vector<bool> > visited(ROW, vector<bool>(COL, 0));
    queue<QPoint> Q; // queue for BFS

    // initialize
    visited[start.x][start.y] = true;
    QPoint s = {start, 0};
    Q.push(s);

    while(!Q.empty()){
        QPoint cur = Q.front();
        Q.pop();

        // reach the end!
        if(cur.pt.x == end.x && cur.pt.y == end.y){
            return cur.dist;
        }

        for(int i = 0; i < 4; i++){
            
            int row = cur.pt.x + rd[i];
            int col = cur.pt.y + cd[i];

            if(isValid(row, col) && !visited[row][col] && mat[row][col]){
                visited[row][col] = true;
                QPoint adj = {{row, col}, cur.dist + 1};
                Q.push(adj);

            }
        } 
    }
    return -1; // cannot find the end
}
