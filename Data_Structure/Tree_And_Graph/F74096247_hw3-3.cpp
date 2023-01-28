#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
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

        /************ BFS **********/
        // 1. use a queue to store the vertex we meet
        // 2. pop the front and store its connected vertex into the queue
        // 3. repeat step 2

        bool  visited[m]; 
        // this is to check if we have visited this vertex
        for(int i = 0; i < m; i++){
            visited[i] = false;
        }

        // start with t
        list<int> Q;
        visited[t] = true;
        Q.push_back(t);

        while(!Q.empty()){
            // get the front of the queue and remove it
            t = Q.front();
            outFile << t << " ";
            Q.pop_front();

            for(int j = 0; j < m ;j++){
                if(matrix[t][j] == 1){
                    // if this vertex is not visited
                    if(!visited[j]){
                        visited[j] = true;
                        Q.push_back(j);
                    }
                }
            }
        }
        outFile << endl;
    }
    outFile.close();
    return 0;
}