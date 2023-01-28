#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;
void path(int startx, int starty, int endx, int endy);

//create a 2D array: maze[17][17]
const int row = 17;
const int col = 17;
int maze[row][col];

int main(){

    /***** main function : load and print out the maze *****/
    // enter the file the user want to load in
    string file = "";
    cout << "enter filename : ";
    cin >> file;

    //load in the maze.txt by using ifstream
    ifstream inFile;
    inFile.open(file);

    int r = 0, c = 0;
    // store the "maze.txt" in the maze[17][17]
    if(inFile.is_open()){

        // line means every line we get in maze.txt
        string line = "";
        while(getline(inFile, line)){
            //get the information line by line
            if(line!=""){

                c = 0;
                for (int i = 0; i < line.length(); i++){
                    maze[r][c] = line[i]-'0'; // to get int but char
                    c++;
                }
                r++;
                // c and r keep track of maze[][], while i keep track of line
            }
        }
    }

    // let's print out the maze[17][17]
    for(int i=0; i<row; i++){
        for( int j=0; j<col;j++){
            cout << maze[i][j];
        }
        cout << endl;
    }

    /***** main function : start to solve the maze *****/

    int start_x = 0, start_y = 0;
    int end_x = 0, end_y = 0;
    // start: to decide when to end the code (when start position: -1 -1) 
    bool start = true;
    while(start){

        // record the start point 
        cout << "enter start position : ";
        cin >> start_x >> start_y;
        if(start_x==-1 && start_y==-1){
            start = false;
            break;
        }
        // record the exut point
        cout << "enter exit position : ";
        cin >> end_x >> end_y;

        path(start_x, start_y,end_x,end_y);
    }

    // if start point = -1 -1, end the code
    cout << "end the code.";
    return 0;
}

/***************** definition of the movement and the stack *********************/

typedef struct
{
    int a; /* move_row */
    int b; /* move_col */
}offsets;

typedef struct{
    int x;
    int y;
    int dir; 
    // dir = 0 ~ 3
    // move[dir] would define which direction to go
}item;

/****************** use the function Path() to print the path in a maze **********************/
void path(int startx, int starty, int endx, int endy){

    // define how to move.
    offsets move[4] = {
        {0, 1},  /* 0: east */
        {1, 0},  /* 1: south */
        {-1, 0}, /* 2: north */
        {0, -1}  /* 3: west */
    };

    // create a 2D array to record whether we have passed through the point    
    // if we have, mark[][] = 1
    int mark[row][col] = {0};
    mark[startx][starty] = 1;

    // create a stack to record our route    
    // initialize and add it into the stack(st)
    stack<item> st;
    item temp;
    temp.x = startx; temp.y = starty; temp.dir = 0;
    st.push(temp);

    // these two ints are used to check where we are,
    // to make sure we won't double print the consequence
    int I =0;
    int J=0;

    // show the number of path when we are tracking
    int number = 0;

    
    while(! st.empty()){ //while the stack is not empty
        temp = st.top();
        st.pop(); //unstack
        int i = temp.x; int j = temp.y; int d = temp.dir;
        bool Printed = false;

        // try the four direction (0~3) to move on
        while(d<4){
            int g = i + move[d].a; int h = j + move[d].b;
            // test the next step
            if((g==endx)&&(h==endy)){

                // if the next step is the exit, print them out.
                // we have to print the last two position, because they're not in the stack
                cout << number<<":"<< i << "," << j << endl;
                number++;
                cout <<number<<":"<< g << "," << h << endl;
                return;
            }
            if((! maze[g][h]) && (!mark[g][h])){
                // maze[][] = 0: the next step is not a wall
                // mark[][] = 0: we haven't been through this place

                mark[g][h] = 1; // record the place => been through
                // put it into the stack, and print it out
                temp.x = i; temp.y = j; temp.dir = 0;
                cout << number<<":"<< i << "," << j << endl;
                number++;
                st.push(temp);
                // go on to the next step.
                i = g; j = h; d = 0;
            }else{
                d++; // to try another direction
                // if last step is as the same as the last one
                // (still looking for the right direction)
                // make sure we won't print it.
                if(i!=I||j!=J){
                    cout << number<<":"<< i << "," << j << endl;
                    number++;
                } 
            }
            I = i;
            J = j;
        }
    }
    cout << "Failed to escape.\n";
    // this means we cannot find the route

    return;
}
