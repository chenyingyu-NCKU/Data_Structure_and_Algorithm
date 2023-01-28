#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

int N;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    vector<int> doll(N);
    vector< vector<int> > order;

    for(int i = 0; i < N; i++){
        cin >> doll[i];
    }

    sort(doll.begin(), doll.end());

    vector<int> arr(1, doll[0]);
    order.push_back(arr);

    for(int i = 1; i < N; i++){

        for(int j = 0; j < order.size(); j++){
            
            int current = order[j].back();

            if(doll[i] > current){
                order[j].push_back(doll[i]);
                break;

            }
            if(j == order.size() - 1){
                vector<int> temp(1, doll[i]);
                order.push_back(temp);
                break;
            }
        }
    }

    for(int i = 0; i < order.size(); i++){
        for(int j = 0; j < order[i].size(); j++){
            cout << order[i][j] << " ";
        }cout << endl;
    }
    

    return 0;
}