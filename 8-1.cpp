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

 
vector<pair<double, double>> findA(char c, vector<vector <char>> input) {
    vector<pair<double, double>> locations;
    for (double i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == c)
            {
                locations.push_back({i, j});
            }
        }
    }
    return locations;
}






vector<pair<double, double>> findB(vector<pair<double, double>> locations, vector<vector <char>> input) {
    int rows = input.size();
    int cols = input[0].size();
    vector<pair<double, double>> signals;

    for (int i = 0; i < locations.size(); i++)
    {
        for (int j = i+1; j < locations.size(); j++)
        {
            double dR = abs(locations[i].first - locations[j].first);
            double dC = abs(locations[i].second - locations[j].second);



            // if x1 = x2

            if (locations[i].first == locations[j].first)
            {
                signals.push_back({locations[i].first, min(locations[i].second, locations[j].second) - dC});
                signals.push_back({locations[j].first, max(locations[i].second, locations[j].second) + dC});
            }

            // if y1 = y2
            else if (locations[i].second == locations[j].second)
            {
                signals.push_back({min(locations[i].first, locations[j].first) - dR, locations[i].second});
                signals.push_back({max(locations[i].first, locations[j].first) + dR, locations[j].second});
            }

            // if x1 < x2

            else if (locations[i].first < locations[j].first)
            {
                // if y1 < y2
                if (locations[i].second < locations[j].second)
                {
                    signals.push_back({locations[i].first - dR, locations[i].second - dC});
                    signals.push_back({locations[j].first + dR, locations[j].second + dC});

                }

                else
                {
                    signals.push_back({locations[i].first - dR, locations[i].second + dC});
                    signals.push_back({locations[j].first + dR, locations[j].second - dC});
                }
            }

            // if x1 > x2
            else
            {
                // if y1 < y2
                if (locations[i].second < locations[j].second)
                {
                    signals.push_back({locations[i].first + dR, locations[i].second - dC});
                    signals.push_back({locations[j].first - dR, locations[j].second + dC});

                }
                
                else
                {
                    signals.push_back({locations[i].first + dR, locations[i].second + dC});
                    signals.push_back({locations[j].first - dR, locations[j].second - dC});

                }
            }
           
           
        }
    }

    // (1, 8)    (2, 5)

    // x1 - sX, y1 - sY          1,    3                    (1,8) (1, 4)     4     
    return signals;

    
}



int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0;

    vector<vector <char>> input;

    while (getline(MyFile, my_string)) {

        string s = my_string;
        int j = 0;
        vector<char> row;

        while (j < s.size())
        {
            row.push_back(s[j]);
            j++;
        }
        input.push_back(row);
    }
    MyFile.close();

    set<pair<int, int>> validS;
    for (char c = 'a'; c <= 'z'; ++c) {
        
        // for each char, go through and find the locations and put in vector
        // find each location and put in vector
        vector<pair<double, double>> locations = findA(c, input);
        
        // find each possible signal (if there are more than two signals)
        if (locations.size() >= 2)
        {        
            vector<pair <double, double>> signals = findB(locations, input);
            
            // only get valid signals
            for (auto  p : signals)
            {
                if (p.first >= 0 && p.first < input.size() 
                && p.second >= 0 && p.second < input[0].size()
                && validS.find(p) == validS.end())
                {
                    cout << "{" << p.first << ", " << p.second << "}" << endl;
                    validS.insert(p);
                    
                }
            }
            

        }        
        
    }

    for (char c = 'A'; c <= 'Z'; ++c) {


        vector<pair<double, double>> locations = findA(c, input);
     
        // find each possible signal (if there are more than two signals)
        if (locations.size() >= 2)
        {        
            vector<pair <double, double>> signals = findB(locations, input);
            
            // only get valid signals
            for (auto  p : signals)
            {
                if (p.first >= 0 && p.first < input.size() 
                && p.second >= 0 && p.second < input[0].size()
                && validS.find(p) == validS.end())
                {
                    validS.insert(p);
                    cout << "{" << p.first << ", " << p.second << "}" << endl;
                
                }
                
            }
            
        }  
       
    }

    for (char c = '0'; c <= '9'; ++c) {
        vector<pair<double, double>> locations = findA(c, input);
       
        // find each possible signal (if there are more than two signals)
        if (locations.size() >= 2)
        {        
            vector<pair <double, double>> signals = findB(locations, input);
            
            // only get valid signals
            for (auto  p : signals)
            {
                if (p.first >= 0 && p.first < input.size() 
                && p.second >= 0 && p.second < input[0].size()
                && validS.find(p) == validS.end())
                {
                    validS.insert(p);
                    cout << "{" << p.first << ", " << p.second << "}" << endl;
                    
                }
                
            }
            
        }  
      
    
    }
    total += validS.size();
    cout << "this is the total: " << total << endl;
}