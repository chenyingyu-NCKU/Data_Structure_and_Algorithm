#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

// https://www.youtube.com/watch?v=vltY5jxqcco

bool mycompare(pair<int, char>& a, pair<int, char>& b);
// input can be little, big, and number
// if frequency is the same, sort with ASCII

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector< pair<int, char> > table('z'-'0'+1);
    string s;
    cin >> s;

    // create a hash table
    for(int i = 0; i < s.length(); i++){
        char c = s[i];
        table[c - '0'] = pair<int, char>(table[c - '0'].first + 1, c);
    }

    // sort it (ascending)
    sort(table.begin(), table.end(), mycompare);

    // print it out
    string ans = "";
    vector< pair<int, char> >::iterator k;
    for(k = table.begin(); k != table.end(); k++){
        ans = string(k->first, k->second) + ans;
        // string(3, a) = aaa
    }
    cout << ans;
    
    return 0;
}
bool mycompare(pair<int, char>& a, pair<int, char>& b){
    if(a.first != b.first){
        return a < b;
    }else{
        return a.second - '0' > b.second - '0';
    }
}
