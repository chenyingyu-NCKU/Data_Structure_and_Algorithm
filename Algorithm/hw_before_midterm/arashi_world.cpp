#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

int N , M;
void move_onto(int a, int b, vector< vector<int> >& v, vector<int>& location);
void move_over(int a, int b, vector< vector<int> >& v, vector<int>& location);
void pile_onto(int a, int b, vector< vector<int> >& v, vector<int>& location);
void pile_over(int a, int b, vector< vector<int> >& v, vector<int>& location);


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> M;

    vector<int> location(N+1);
    vector< vector<int> > v(N+1);
    // initialize the vector v (represent the visual look)
    // location means the row(location) i is at
    for(int i = 1; i < N+1 ; i++){
        v[i].push_back(i);
        location[i] = i;
    }

    int a, b;
    string c1, c2;
    for(int i = 0; i < M; i++){
        cin >> c1 >> a >> c2 >> b;

        if( a == b || location[a] == location[b]){
            continue;
        }

        if(c1 == "move" && c2 == "onto"){
            move_onto(a, b, v, location);
        }if(c1 == "move" && c2 == "over"){
            move_over(a, b, v, location);
        }if(c1 == "pile" && c2 == "onto"){
            pile_onto(a, b, v, location);
        }if(c1 == "pile" && c2 == "over"){
            pile_over(a, b, v, location);
        }
        
    }

    cout << endl;
    for(int i = 1; i < N+1; i++){
        cout << i << ":";
        for(int j = 0; j < v[i].size(); j++){
            cout << " " << v[i][j];
        }
        cout << endl;
    }
    return 0;
}

/*********** my fuction ***********/

void move_onto(int a, int b, vector< vector<int> >& v, vector<int>& location){

    int pos_a, pos_b; // a's position = v [location[a]] [pos_a]
    int la = location[a], lb = location[b];

    for(int j = 0; j < v[la].size(); j++){
        if(v[la][j] == a){
            pos_a = j;
        }
    }for(int j = 0; j < v[lb].size(); j++){
        if(v[lb][j] == b){
            pos_b = j;
        }
    }

    // clean the numbers stack on a, b
    for(int j = v[la].size()-1; j > pos_a; j--){
        int c = v[la][j];
        v[la].erase(v[la].begin() + j);
        location[c] = c;
        v[location[c]].push_back(c);
    }
    for(int j = v[lb].size()-1; j > pos_b; j--){
        int c = v[lb][j];
        v[lb].erase(v[lb].begin() + j);
        location[c] = c;
        v[location[c]].push_back(c);
    }

    // put a on b
    location[a] = location[b];
    v[lb].push_back(a);
    v[la].erase(v[la].begin() + pos_a);
}
void move_over(int a, int b, vector< vector<int> >& v, vector<int>& location){

    int pos_a; // a's position = v [location[a]] [pos_a]
    int la = location[a];

    for(int j = 0; j < v[la].size(); j++){
        if(v[la][j] == a){
            pos_a = j;
        }
    }
    // clean the numbers stack on a
    for(int j = v[la].size()-1; j > pos_a; j--){
        int c = v[la][j];
        v[la].erase(v[la].begin() + j);
        location[c] = c;
        v[location[c]].push_back(c);
    }

    // put a on b stack
    location[a] = location[b];
    v[location[b]].push_back(a);
    v[la].erase(v[la].begin() + pos_a);
}
void pile_onto(int a, int b, vector< vector<int> >& v, vector<int>& location){

    int pos_a, pos_b; // a's position = v [location[a]] [pos_a]
    int la = location[a], lb = location[b];

    for(int j = 0; j < v[la].size(); j++){
        if(v[la][j] == a){
            pos_a = j;
        }
    }for(int j = 0; j < v[lb].size(); j++){
        if(v[lb][j] == b){
            pos_b = j;
        }
    }

    // clean the numbers stack on b
    for(int j = v[lb].size()-1; j > pos_b; j--){
        int c = v[lb][j];
        v[lb].erase(v[lb].begin() + j);
        location[c] = c;
        v[location[c]].push_back(c);
    }

    // pile a stack onto b
    for(int j = pos_a; j < v[la].size(); j++){
        int c = v[la][j];
        location[c] = location[b];
        v[lb].push_back(c);
    }// erase a stack 
    for(int j = v[la].size()-1; j >= pos_a; j--){
        v[la].erase(v[la].begin() + j);
    } 
}
void pile_over(int a, int b, vector< vector<int> >& v, vector<int>& location){

    int pos_a; // a's position = v [location[a]] [pos_a]
    int la = location[a], lb = location[b];

    for(int j = 0; j < v[la].size(); j++){
        if(v[la][j] == a){
            pos_a = j;
        }
    }

    // pile a stack onto b
    for(int j = pos_a; j < v[la].size(); j++){
        int c = v[la][j];
        location[c] = location[b];
        v[lb].push_back(c);
    }// erase a stack 
    for(int j = v[la].size()-1; j >= pos_a; j--){
        v[la].erase(v[la].begin() + j);
    } 
}


