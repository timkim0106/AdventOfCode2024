#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;



void dfs(vector<vector<char> > &grid, int row, int col, int &total) {
    // Get grid dimensions
    int numRows = grid.size();
    int numCols = grid[0].size();

    // 2 possible diagonal lines checked
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, -1));  
    directions.push_back(make_pair(1, -1)); 

    bool cond1 = false;
    bool cond2 = false;

    // Traverse all adjacent cells
    for (int i = 0; i < directions.size(); i++)
    {   
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;
        int newRow2 = row - directions[i].first;
        int newCol2 = col - directions[i].second;

        
        if (newRow >=0 && newRow < numRows && newCol >=0 && newCol < numCols && grid[newRow][newCol] == 'M' 
         && newRow2 >=0 && newRow2 < numRows && newCol2 >=0 && newCol2 < numCols && grid[newRow2][newCol2] == 'S')
        {
            if (i == 0)
            {
                cond1 = true;
            }
            else
            {
                cond2 = true;
            }
        }
        else if (newRow >=0 && newRow < numRows && newCol >=0 && newCol < numCols && grid[newRow][newCol] == 'S' 
         && newRow2 >=0 && newRow2 < numRows && newCol2 >=0 && newCol2 < numCols && grid[newRow2][newCol2] == 'M')
         {
            if (i == 0)
            {
                cond1 = true;
            }
            else
            {
                cond2 = true;
            }
         }
    }

    if (cond1 && cond2)
    {
        total++;
    }
    
}


int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0;
    int n = 0;
    bool toDo = true; 

    vector<vector<char> > wordSearch;
    int i = 0;

    while (getline(MyFile, my_string)) {
    
        string s = my_string;
        int j = 0;
        vector<char> row;

        while (j < s.size())
        {
            row.push_back(s[j]);
            j++;
        }
        wordSearch.push_back(row);
        i++;
    }



    for (int i = 0; i < wordSearch.size(); i++)
    {
        for (int j = 0; j < wordSearch[i].size(); j++)
        {
            if (wordSearch[i][j] == 'A')
            {
                cout << "this is i: " << i << endl;
                cout << "this is j: " << j << endl;

                dfs(wordSearch, i, j, total);
                cout << "this is total: " << total << endl;
            }


        }
    }

    cout << total << endl;
    MyFile.close();
    return 0;
}
