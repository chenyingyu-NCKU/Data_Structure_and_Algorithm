#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <iterator> // error on online compiler
#include <algorithm>

using namespace std;

int N;
set<string> empty_set;
stack< set<string> > mystack;
int add_set();
int inter_set();
int uni_set();

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> ans(N);

    for(int i = 0; i < N; i++){
        string s;
        cin >> s;

        if(s == "PUSH"){
            ans[i] = 0;
            mystack.push(empty_set);
        }
        if(s == "DUP"){
            set<string> temp = mystack.top();
            ans[i] = temp.size();
            mystack.push(temp);
        }
        if(s == "ADD"){
            ans[i] = add_set();
        }if(s == "INTERSECT"){
            ans[i] = inter_set();
        }if(s == "UNION"){
            ans[i] = uni_set();
        }
    }

    for(int i = 0; i < N; i++){
        cout << ans[i] << endl;
    }
    
    return 0;
}
int add_set(){

    set<string> t1 = mystack.top();
    mystack.pop();
    set<string> t2 = mystack.top();
    mystack.pop();

    // turn t1 into a string
    ostringstream stream;
    copy(t1.begin(), t1.end(), ostream_iterator<string>(stream, ","));
    string s = "{" + stream.str() + "}";

    // insert the string into t2;
    t2.insert(s);
    // put it back to the stack
    mystack.push(t2);

    return t2.size();
}
int inter_set(){

    set<string> t1 = mystack.top();
    mystack.pop();
    set<string> t2 = mystack.top();
    mystack.pop();

    // get the intersection of t1 and t2
    set<string> intersect;
    set_intersection(t1.begin(), t1.end(), t2.begin(), t2.end(), inserter(intersect, intersect.begin()));

    // put it back to stack
    mystack.push(intersect);
    return intersect.size();
}
int uni_set(){

    set<string> t1 = mystack.top();
    mystack.pop();
    set<string> t2 = mystack.top();
    mystack.pop();

    // get the union of t1 and t2
    set<string> uni;
    set_union(t1.begin(), t1.end(), t2.begin(), t2.end(), inserter(uni, uni.begin()));

    // back to stack
    mystack.push(uni);
    return uni.size();
}

    