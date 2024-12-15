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

 


int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 1;

    vector<vector < char> > lab;
    int i = 0;
    int currCol, currRow;

    vector<pair<int, int> > visited2;
    set<pair<int, int> > visited3;


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

    MyFile.close();

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
    vector<int> currPos;
    currPos.push_back(currRow);
    currPos.push_back(currCol);
    visited3.insert(make_pair(currRow, currCol));

    bool inLab = true;
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, 0)); 
    directions.push_back(make_pair(0, 1));  
    directions.push_back(make_pair(1, 0)); 
    directions.push_back(make_pair(0, -1));
    int d = 0;
    while (inLab)
    {

        currRow = currRow + directions[d].first;
        currCol = currCol + directions[d].second;
        
        if (currRow < 0 || currRow >= lab.size() || currCol < 0 || currCol >= lab[0].size())
        {
            inLab = false;
            
        }
        else if (lab[currRow][currCol] == '#')
        {
            currRow = currRow - (directions[d].first);
            currCol = currCol - (directions[d].second);
            d = (d + 1) % 4;    
        }
        else
        {
            pair<int, int> p = {currRow, currCol};
            if (visited3.find(p) == visited3.end())
            {
                visited3.insert(p);
                total++;
            }
            else
            {
                cout << "already visited the spot " << endl;
            }
        }
        cout << total << " " << d << endl;
        cout << "visited size: " << visited2.size() << endl;


        

    }
    cout << total << endl;

}
