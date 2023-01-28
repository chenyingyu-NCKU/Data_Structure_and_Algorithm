#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

int T;
int jump_distance_max(vector< pair<int, char> >& go, vector< pair<int, char> >& back, int meter);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    vector<int> ans(T);

    for(int i = 0; i < T; i++){
        int N, Meter;
        cin >> N >> Meter;

        vector< pair<int, char> > go;
        vector< pair<int, char> > back;

        int small = 0;
        for(int j = 0; j < N; j++){
            char symbol;
            int position;
            cin >> symbol >>position;

            pair<int, char> stone(position, symbol);

            if(symbol == 's'){
                if(small%2 == 0) go.push_back(stone);
                else back.push_back(stone);

                small++;
            }else{
                go.push_back(stone);
                back.push_back(stone);
            }
        }

        // for(int i = 0; i < go.size(); i++){
        //     cout << go[i].first << " ";
        // }cout << endl;
        // for(int i = 0; i < back.size(); i++){
        //     cout << back[i].first << " ";
        // }

        ans[i] = jump_distance_max(go, back, Meter);
    }

    for(int i = 0; i < T; i++){
        cout << ans[i] << endl;
    }
    return 0;
}
int jump_distance_max(vector< pair<int, char> >& go, vector< pair<int, char> >& back, int meter){
    
    pair<int, char> start_(0, 'g');
    pair<int, char> end_(meter, 'g'); // ground

    go.insert(go.begin(), start_);
    go.push_back(end_);
    back.insert(back.begin(), start_);
    back.push_back(end_);

    int max_dis = 0;

    for(int i = 0; i < go.size()-1; i++){
        max_dis = max(max_dis, go[i+1].first - go[i].first);
    }
    for(int i = back.size() -1 ; i > 0; i--){
        max_dis = max(max_dis, back[i].first - back[i-1].first);
    }

    return max_dis;
}
