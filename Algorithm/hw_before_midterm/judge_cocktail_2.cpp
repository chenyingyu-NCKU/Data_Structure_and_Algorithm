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


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M_each >> K_th;

    multiset<int> cocktaile;
    vector<int> arr(N);
    vector<int>ans;

    for(int i = 0; i < N ; i++){
        cin >> arr[i];
    }

    // create the base of the set
    cocktaile.insert(arr[0]);
    multiset<int> :: iterator it = cocktaile.begin(); // the smallest

    int m = 1; // m elements in set, at most M
    int arr_p = 0;
    int k_smallest = 1; // now it is the 1st smallest in the set

    if(M_each == 1){
        ans = arr;
    }else{

        for(int i = 1; i < N; i++){
            // push in the set
            int concern = arr[i]; // concerntration
            cocktaile.insert(concern);
            m++;

            if(k_smallest < K_th){
                if(concern >= *it){
                    it++;
                    k_smallest++;
                }else{
                    k_smallest++;
                }
            }else if(k_smallest == K_th){
                // if concern > *it won't change
                if(concern < *it){
                    it--;
                }
            }

            if(m == M_each){
                ans.push_back(*it);

                // remove arr[p] from set
                if(arr[arr_p]<= *it){
                    it++;
                    if(it == cocktaile.end()){
                        it--;
                        
                        // when removing one is it
                        multiset<int> :: iterator temp = it;
                        if(arr[arr_p] == *it && *--temp != *it){
                            it--;
                        }
                        k_smallest--;
                    }
                    
                }

                cocktaile.erase(cocktaile.find(arr[arr_p]));
                arr_p++;
                m--;
            }
        }
    }

    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }

    return 0;
}

