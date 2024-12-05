#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;



void dfs(vector<vector<char> > &grid, int row, int col, int &total) {
    // Get grid dimensions
    int numRows = grid.size();
    int numCols = grid[0].size();

    // 8 possible directions
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, 0)); 
    directions.push_back(make_pair(1, 0));  
    directions.push_back(make_pair(0, -1)); 
    directions.push_back(make_pair(0, 1));  
    directions.push_back(make_pair(-1, -1)); 
    directions.push_back(make_pair(1, 1));  
    directions.push_back(make_pair(1, -1));
    directions.push_back(make_pair(-1, 1));  

    // Traverse all adjacent cells
    for (int i = 0; i < directions.size(); i++)
    {   
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        
        if (newRow >=0 && newRow < numRows && newCol >=0 && newCol < numCols && grid[newRow][newCol] == 'M')
        {
            newRow += directions[i].first;
            newCol += directions[i].second;
            
            if (newRow >=0 && newRow < numRows && newCol >=0 && newCol < numCols &&
            grid[newRow][newCol] == 'A') 
            {
                newRow += directions[i].first;
                newCol += directions[i].second;
            
                if (newRow >=0 && newRow < numRows && newCol >=0 && newCol < numCols &&
                grid[newRow][newCol] == 'S') 
                {
                    total++;
                }
            }
        }
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
            if (wordSearch[i][j] == 'X')
            {
                dfs(wordSearch, i, j, total);
            }


        }
    }

    cout << total << endl;
    MyFile.close();
    return 0;
}
