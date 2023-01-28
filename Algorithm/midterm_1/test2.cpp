#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <iterator>
using namespace std;

int N;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> arr(N);
    vector<int> s(N);
    vector<int> ans(N, 0);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
        s[i] = arr[i];
    }

    sort(s.begin(), s.end());

    for(int i = 0; i < N; i++){
        vector<int>::iterator pos;

        pos = find(s.begin(), s.end(), arr[i]);
        s.erase(pos);
        int temp = pos - s.begin();
        ans[i] = temp;
    }    

    for(int i = 0; i < N; i++){
        cout << ans[i] << " ";
    }
    return 0;
}