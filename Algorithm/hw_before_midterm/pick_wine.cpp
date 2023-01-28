#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

int N;
int Q;
vector<int> line(10000001,0);
int pickWine(int jdg_position, int favor_concen);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> Q;

    for(int i = 0; i < N; i++){
        int position = 0;
        int concen = 0;
        cin >> position >> concen;

        line[position] = concen;
    }

    vector<int> out;
    for(int i = 0; i < Q; i++){
        int position = 0;
        int favor_concen = 0;
        cin >> position >> favor_concen;

        int ans = pickWine(position, favor_concen);
        out.push_back(ans);
    }

    for(int i = 0; i < out.size(); i++){
        cout << out[i] << endl;
    }

    return 0;
}
int pickWine(int jdg_position, int favor_concen){
    int ans = -1;

    int range = 0;
    while((jdg_position + range < 10000001) || (jdg_position - range >= 0)){

        int pos_posi = min(jdg_position + range, 10000001);
        int neg_posi = max(jdg_position - range, 0);

        if(line[neg_posi] >= favor_concen){
            ans = neg_posi;
            break;
        }
        if(line[pos_posi] >= favor_concen){
            ans = pos_posi;
            break;
        }

        range ++;
    }

    return ans;
}
