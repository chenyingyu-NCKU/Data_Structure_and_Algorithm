#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <climits>
using namespace std;

const int N = 200100;
const int INF = INT_MAX;
int obtain_the_string(string s, string t);

int T;
string t, s;
int arr[N][26];

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    vector<int> ans(T); 

    for(int k = 0; k < T; k++){
        cin >> s >> t;

        ans[k] = obtain_the_string(s, t);
    }

    for(int k = 0; k < T; k++){
        cout << ans[k] << endl;
    }

    return 0;
}
int obtain_the_string(string s, string t){

        // initialize
        for(int i = 0; i < s.length() + 1; i++){
            for(int j = 0; j < 26; j++){
                arr[i][j] = INF;
            }
        }
    	
        // when i = 0
        // arr[i] means from i to |s|
        // where is the idex of j(0~25 => a~z)
        //
        // s = axy
        // arr[0] = 0 INF INF ... 1 2 INF (present a-z)
        // arr[1] = INF INF ... 1 2 INF
        // arr[2] = INF INF ... INF 2 INF

        for(int i = s.length() - 1; i >= 0; i--){
            for(int j = 0; j < 26; j++){
                arr[i][j] = arr[i+1][j];
            }
            arr[i][s[i] - 'a'] = i;
        }    

        // Now we can solve this problem by simple greed. 
        // Presume that now z = t0t1...t(i-1), and last taken symbol in s is spos. Then there are two options:

        // if arr[pos][i] != INF, then i++, pos = arr[pos+1][i];
        // if arr[pos][i] == INF, then pos = 0 and ans++ (ans is equal to 0 initially);

        int result = 1, pos = 0;
        for(int i = 0; i < t.length(); i++){
            if(pos == s.length()){
                pos = 0;
                result++;
            }
            if(arr[pos][t[i] - 'a'] == INF){
                pos = 0; 
                result++;
    		}
    		if(arr[pos][t[i] - 'a'] == INF && pos == 0){
                result = INF;
                break;
            }    
            pos = arr[pos][t[i] - 'a'] + 1;
            
        }
    
        if(result >= INF) return -1;
        else return result;
}

