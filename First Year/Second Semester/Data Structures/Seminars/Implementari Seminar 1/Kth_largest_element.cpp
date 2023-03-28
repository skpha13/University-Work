#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int findKthLargest(vector<int>& nums, int k) {
    make_heap(nums.begin(),nums.end());
    for(int i=0;i<k-1;i++)
    {
        pop_heap(nums.begin(),nums.end());
        nums.pop_back();
    }
    return nums.front();
}

int main()
{
    int k = 4;
    vector<int> v = {3,2,3,1,2,4,5,5,6};    
    cout<<findKthLargest(v,k);
    return 0;
}