#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
int K;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    vector< pair<float, string> > cocktail;

    for(int i = 0; i < N; i++){
        float a, b, c;
        string name;

        cin >> a >> b >> c >> name;

        float concern = (c*1000/(a+b+c));

        pair<float, string> item(concern, name);
        cocktail.push_back(item);
    }

    

    sort(cocktail.begin(), cocktail.end());

    // cout << "----" << endl;
    // for(int i = 0; i < N; i++){
    //     cout << cocktail[i].first << " " << cocktail[i].second << endl;
    // }cout << "-----" << endl;

    cout << cocktail[N-K].second;

    return 0;
}