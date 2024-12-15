#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

 
// Recursive function to evaluate all combinations
void evaluate(const vector<long long>& nums, int index, long long current, unordered_set<long long>& results) {
    // Base case: if we've processed all numbers, store the result
    if (index == nums.size()) {
        results.insert(current);
        return;
    }

    // Recursive case: apply addition and multiplication
    evaluate(nums, index + 1, current + nums[index], results); // Addition
    evaluate(nums, index + 1, current * nums[index], results); // Multiplication
}

bool reachGoal(vector<long long> &v, long long goal)
{
    unordered_set<long long> results;
    evaluate(v, 1, v[0], results);


    for (long long n : results)
    {
        if (n == goal)
        {
            return true;
        }
    }
    return false;
    // a1 a2 a3     a1 + a2 + a3     a1 + a2 * a3   a1 * a2 + a3   a1 * a2 * a3

}

int main() {
    ifstream MyFile("input.txt");
    string my_string;
    long long total = 0;

    vector<long long> v;

    while (getline(MyFile, my_string)) {
    
        string s = my_string;
        stringstream ss(s);
        string token;

        vector<long long> v;

        while (getline(ss, token, ' '))
        {
            long long t = stoll(token);
            v.push_back(t);
        }
    
        cout << v.size() << endl;
        long long goal = v[0];
        v.erase(v.begin());

        // check if we can reach goal
        if (reachGoal(v, goal))
        {
            total += goal;

            cout << "this is valid goal: " << goal << endl;
        }
    




    }
    MyFile.close();

    cout << "this is the total: " << total << endl;
}