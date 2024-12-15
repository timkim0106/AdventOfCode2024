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

 

bool run(vector<vector <char>> &lab, int i, int j, int currI, int currJ)
{

    lab[i][j] = '#';

    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, 0)); 
    directions.push_back(make_pair(0, 1));  
    directions.push_back(make_pair(1, 0)); 
    directions.push_back(make_pair(0, -1));
    int d = 0;
    int currCol = currJ; int currRow = currI;
    vector<int> currPos;
    currPos.push_back(currRow);
    currPos.push_back(currCol);
    set<pair<pair<int, int>, int>> visited;
    visited.insert(make_pair(make_pair(currRow, currCol), d));
    while (true)
    {
        currRow = currRow + directions[d].first;
        currCol = currCol + directions[d].second;
        if (currRow < 0 || currRow >= lab.size() || currCol < 0 || currCol >= lab[0].size())
        {
            lab[i][j] = '.';
            return false;
        }
        else if (visited.find(make_pair(make_pair(currRow, currCol), d)) != visited.end())
        {
            lab[i][j] = '.';
            cout << "found valid cycle: " << i << " and " << j << endl;
            return true;
        }
        else if (lab[currRow][currCol] == '#')
        {
            currRow = currRow - (directions[d].first);
            currCol = currCol - (directions[d].second);
            visited.insert(make_pair(make_pair(currRow, currCol), d));
            d = (d + 1) % 4;  
        }
        else 
        {
            visited.insert(make_pair(make_pair(currRow, currCol), d));  
        }
    }



    lab[i][j] = '.';
    return true;
}


int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0;

    vector<vector < char> > lab;
    int i = 0;
    int currCol, currRow;

    vector<pair<int, int> > visited2;
    set<pair<int, int> > visited3;

    // visited can have i, j, and direction. if we find same, then its a cycle

    while (getline(MyFile, my_string)) {
    
        string s = my_string;
        int j = 0;
        vector<char> row;

        while (j < s.size())
        {
            row.push_back(s[j]);
            j++;
        }
        lab.push_back(row);
        i++;
    }


    
    // find original position
    for (int i = 0; i < lab.size(); i++)
    {
        for (int j = 0; j < lab[i].size(); j++)
        {
            if (lab[i][j] == '^')
            {
                currRow = i;
                currCol = j;
            }
        }
    }

    // try putting obstacle in every possible location
    for (int i = 0; i < lab.size(); i++)
    {
        for (int j = 0; j < lab[i].size(); j++)
        {

            if (lab[i][j] == '.')
            {
                // run
                bool valid = run(lab, i, j ,currRow, currCol);
                if (valid)
                {
                    total++;
                }

            }

        }
    }

    cout << total << endl;
    MyFile.close();
}