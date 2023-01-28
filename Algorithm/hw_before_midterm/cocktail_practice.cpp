#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

int N;
int K;
map <string , int> cocktail;
bool mycompare(pair <int, string>& a, pair <int, string>& b);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    for(int i = 0; i < N; i++){
        string name;
        cin >> name;

        // can find name in cocktail
        if(cocktail.find(name) != cocktail.end()){
            cocktail[name]++;
        }else{
            cocktail[name] = 1;
        }
    }

    // convert map to vector
    map <string, int>::iterator i;
    vector< pair<int, string> > array(cocktail.size());
    int j = 0;
    for(i = cocktail.begin(); i != cocktail.end(); i++){
        array[j] = pair<int, string>(i->second, i->first);
        j++;
    }

    sort(array.begin(), array.end(), mycompare);

    // cout << "----" << endl;
    // for(int i = 0; i < array.size(); i++){
    //     cout << array[i].first << " "<< array[i].second << endl;
    // }
    cout << array[K-1].second;


    return 0;
}
// descending
bool mycompare(pair <int, string>& a, pair <int, string>& b){
    if(a.first != b.first){
        return a > b;
    }else{
        return a.second < b.second;
    }
}
