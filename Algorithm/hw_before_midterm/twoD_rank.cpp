#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

int n;
vector<int> rank_of_array(300000, 0); // the output

void rank_2d(vector< vector<int> >& point, vector< vector<int> >& temp, int left, int right);
void merge_and_count(vector< vector<int> >& point, vector< vector<int> >& temp, int left, int mid, int right);

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector< vector<int> > point(n, vector<int>(3, 0)); // point (x, y, index)
    vector< vector<int> > temp(n, vector<int>(3, 0));
    
    for(int i = 0; i < n; i++){
        cin >> point[i][0] >> point[i][1];
        point[i][2] = i;
    }

    sort(point.begin(), point.end()); // sort by x
    rank_2d(point, temp, 0, n-1);

    for(int i = 0; i < n; i++){
        cout << rank_of_array[i] << " ";
    }

    return 0;
}
void rank_2d(vector< vector<int> >& point, vector< vector<int> >& temp, int left, int right){
    // this is the merge sort
    int mid;
    if(right > left){
        mid = (left + right)/ 2;

        // recursion for left and right parts
        rank_2d(point, temp, left, mid);
        rank_2d(point, temp, mid+1, right);

        // merge the left and right subarrays
        merge_and_count(point, temp, left, mid, right);
    }
    return;
}
void merge_and_count(vector< vector<int> >& point, vector< vector<int> >& temp, int left, int mid, int right){

    int l = mid, r = right; // point to the last element of left and right subarray
    // leftsub: left ~ mid; rightsub: mid + 1 ~ right
    int k = right; // pointer for the new array temp (the merged array)

    while((l >= left) && (r >= mid + 1)){
        if(point[l][1] > point[r][1]){
            temp[k][0] = point[l][0];
            temp[k][1] = point[l][1];
            temp[k][2] = point[l][2];
            k--; l--;
        }else{
            temp[k][0] = point[r][0];
            temp[k][1] = point[r][1];
            temp[k][2] = point[r][2];            

            // cout << "this is rank plus: " << point[r][1] << endl;
            rank_of_array[point[r][2]] += (l - left + 1);
            k--, r--;
        }
    }
    while(l >= left){
        temp[k][0] = point[l][0];
        temp[k][1] = point[l][1];
        temp[k][2] = point[l][2];
        k--; l--;
    }while (r >= mid + 1){
        temp[k][0] = point[r][0];
        temp[k][1] = point[r][1];
        temp[k][2] = point[r][2];            
        k--, r--;
    }
    for(int i = left; i <= right; i++){
        point[i][0] = temp[i][0];
        point[i][1] = temp[i][1];
        point[i][2] = temp[i][2];
    }
    return;
}

