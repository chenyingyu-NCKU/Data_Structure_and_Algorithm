#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <iterator> 


using namespace std;
int get_memo(int a);
void set_memo(int a, int b);
int N, M;
vector< pair<int, int> > memo;
vector<int> ans;


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // get N and M
    M = 0, N = 0;
    string get_s = "", t = "";
    getline(cin, get_s);

    int k = 0;
    stringstream stream(get_s);
    while(getline(stream, t, ' ')){
        if(k == 0) N = stoi(t);
        if(k == 1) M = stoi(t);
        k++;
    }

    // get line 
    int a = 0, b = 0;
    for(int i = 0; i < M ; i++){
        getline(cin, get_s);
        stringstream st(get_s);
        k = 0;
        vector<string> keyword(3, "");

        while(getline(st, t, ' ')){
            keyword[k] = t;
            k++;
        }

        if(keyword[0] == "get"){
            a = stoi(keyword[1]);

            int result = get_memo(a);
            ans.push_back(result);

        }if(keyword[0] == "set"){
            a = stoi(keyword[1]);
            b = stoi(keyword[2]);

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
    if(memo.size() == 0) return -1;
    for(int i = 0; i < memo.size(); i++){
        if(memo[i].first == a){
            int ans = memo[i].second;
            
            // renew the pos_a
            memo.erase(memo.begin()+i);
            memo.push_back(pair<int, int>(a, ans));

            return ans;
        }
    }
    return -1;
}
void set_memo(int a, int b){
    // step1: check if a is in the memo
    // step2: if so, erase it, and push the new pair in the memo
    // step3: if no, than we check if memo is full
    // step4: Not Full, push the pair
    // step5: Full, pop front, push back

    bool a_in_memo = false;
    int a_pos = 0;

    // check if a is in the memo
    for(int i = 0; i < memo.size(); i++){
        if(memo[i].first == a){
            a_in_memo = true; 
            a_pos = i; break;
        }
    }

    // if so, erase it, and push the new pair in the memo
    // if no, than we check if memo is full
    if(a_in_memo){
        memo.erase(memo.begin() + a_pos);
        memo.push_back(pair<int, int>(a, b));
        return;
    }else{
        // Not Full, push the pair
        // Full, pop front, push back
        if(memo.size() == N){
            // memo is full
            memo.erase(memo.begin());
            memo.push_back(pair<int, int>(a,b));
            return;
        }else{
            memo.push_back(pair<int, int>(a, b));
            return;
        }
    }

}