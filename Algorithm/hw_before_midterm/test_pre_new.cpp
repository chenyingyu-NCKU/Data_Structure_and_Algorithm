#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <iterator> 
#include <map>


using namespace std;
int get_memo(int a);
void set_memo(int a, int b);
int N, M, cur;
int info[500001][2] = {0}; // info[a][0] = b, info[a][1] = position
// make there's enough memory
map<int, int> memo; // (position, a)
vector<int> ans;


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // get N and M
    M = 0, N = 0, cur = 1;
    cin >> N >> M;

    // get line 
    int a = 0, b = 0;
    string keyword = "";
    for(int i = 0; i < M ; i++){
        cin >> keyword;
        if(keyword == "get"){
            cin >> a;
            int result = get_memo(a);
            ans.push_back(result);

        }if(keyword == "set"){
            cin >> a >> b;
            set_memo(a, b);
        }
    }
    // print out the answer
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
    }

    return 0;
}

int get_memo(int a){

    // info[a][0] = b; info[a][1] = cur_position
    map<int, int>::iterator pos_a;
    pos_a = memo.find(info[a][1]);

    if(pos_a != memo.end() ){
        int b = info[a][0];
        memo.erase(info[a][1]);
        memo[cur] = a;
        info[a][1] = cur;
        cur++;
        return b;
    }
    return -1;
}
void set_memo(int a, int b){

     // info[a][0] = b; info[a][1] = cur_position
    map<int, int>::iterator pos_a;
    pos_a = memo.find(info[a][1]);

    if(pos_a != memo.end() ){
        memo.erase(info[a][1]);
        memo[cur] = a;
        info[a][0] = b;
        info[a][1] = cur;
        cur++;
        return;
    }else{
        if(memo.size() == N){
            memo.erase(memo.begin());
        }
        memo[cur] = a;
        info[a][0] = b;
        info[a][1] = cur;
        cur++;
        return;
    }

}