#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
using namespace std;


int main(){

    int n; // how many datasets

    // enter the file the user want to load in
    string file = "";
    cout << "Please input the file name: ";
    cin >> file;

    //load in the file.txt by using ifstream
    ifstream inFile;
    inFile.open(file);

    // MAKE SURE we successfully load the file
    if(inFile.is_open()){
        // get "n" (how many times should we do)
        string firstline = "";
        getline(inFile,firstline);
        n = stoi(firstline);
    }

    // create a output file
    string outfile_name;
    outfile_name.assign(file, 2, file.length()-2);
    outfile_name = "out" + outfile_name;
    ofstream outFile(outfile_name);


    // there are n datasets
    for(int x = 0; x < n; x++){
        // get m and t line (string)
        string mt_string = "";
        getline(inFile, mt_string);

        int m, t;

        // get m and t by split string with space
        stringstream mt_stream(mt_string);
        string mt;
        int a = 0;
        while (getline(mt_stream, mt, ' ')){
            if(a == 0)
                m = stoi(mt);
            else if(a == 1)
                t = stoi(mt);
            a++;
        }

        int matrix[m][m];
        string line = "";
        for(int i = 0; i < m; i++){
            getline(inFile, line);

            // fill the matrix
            // get each value by split line with space
            stringstream strstream(line);
            string value;
            int j = 0;
            while(getline(strstream, value, ' ')){
                matrix[i][j] = stoi(value);
                j++;
            }
        }

        /************ DFS **********/
        // 1. start with t we get from input, store it into ans
        // 2. if t is connected to the vertex that has not been stored into ans
        // 3. we go to that vertex and store the value into ans
        // 4. if it has been visited, ignore it
        // 5. if this vertex doesn't have more route to go, we go back to the previous vertex
         
        int ans[m];
        ans[0] = t;
        int track = 1;
        while(track < m){
        // while visit is not full 
            for(int j = 0; j < m; j++){
                if(matrix[t][j] == 1){
                    matrix[t][j] = 0;
                    matrix[j][t] = 0;

                    bool visited = false;

                    for(int k = 0; k < track; k++){
                        if(ans[k] == j){
                        // this vertex has been visited
                        visited = true;
                        }
                    }

                    if(visited){
                        // don't store ans t remains t
                        break;
                    }else{
                        // record the answer
                        // move to the j row
                        ans[track] = j;
                        track++;
                        t = j;
                        break;
                    }
                }

                // if there's no other road in this vertex
                if(j == m-1 && matrix[t][j] == 0){
                    // go back to the last vertex
                    for(int k = 0; k < track; k++){
                        if(ans[k] == t){
                            t = ans[k-1];
                        }
                    }
                }
            }
        }

        // write the ans into output file
        for(int i = 0; i < m; i++){
            outFile << ans[i] << " ";
        }
        outFile << endl;
    }
    outFile.close();

    return 0;
}