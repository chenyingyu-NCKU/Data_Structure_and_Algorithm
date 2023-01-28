#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include<climits>
using namespace std;

int n;
int maxSubArraySum(vector<int>& arr, int size);

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	cin >> n;

	vector<int> arr(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}

	int max_sum = maxSubArraySum(arr, n);
	return 0;
}

int maxSubArraySum(vector<int>& arr, int size)
{
	int max_so_far = INT_MIN; // global max
	int max_ending_here = 0; // local max
	int start = 0, end = 0, s=0;
	// s point to the last positive position

	for (int i=0; i< size; i++ )
	{
		max_ending_here += arr[i];

		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			start = s;
			end = i;
		}

		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			s = i + 1;
		}
	}
	cout << "Maximum contiguous sum is "
		<< max_so_far << endl;
	cout << "Starting index "<< start
		<< endl << "Ending index "<< end << endl;

    return max_so_far;
}
