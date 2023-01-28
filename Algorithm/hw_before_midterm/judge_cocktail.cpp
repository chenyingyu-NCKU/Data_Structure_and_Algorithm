#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <iterator>
using namespace std;

int N;
int M_each;
int K_th;
multiset<int> cocktaile;
vector<int>ans;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M_each >> K_th;

    vector<int> arr(N);

    int m = 0;
    int p = 0; // pointer to the array
    for(int i = 0; i < N; i++){
        int concern;
        cin >> concern;
        arr[i] = concern;

        cocktaile.insert(concern);
        m++;
        
        if(m == M_each){
            multiset<int> :: iterator it = cocktaile.begin();
            advance(it, K_th -1);
            ans.push_back(*it);

            cocktaile.erase(cocktaile.find(arr[p]));
            p++;
            m--;
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }

    return 0;
}

