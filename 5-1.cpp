#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;



void readLine(string &s, vector<pair<int, int> >&rules)
{
    int n1 = stoi(s.substr(0,2));
    int n2 = stoi(s.substr(3,2));
    pair<int, int> p = make_pair(n1, n2);
    rules.push_back(p);
}

int checkLine(string &s, vector<pair<int, int> > &rules)
{
    stringstream ss(s);
    vector<int> v;
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));

    }

    for (int i = 0; i < rules.size(); i++)
    {
        
        auto it1 = find(v.begin(), v.end(), rules[i].first);
        auto it2 = find(v.begin(), v.end(), rules[i].second);
        if (it1 != v.end() && it2 != v.end())
        {
            int idx1 = std::distance(v.begin(), it1);
            int idx2 = std::distance(v.begin(), it2);
            if (idx1 >= idx2) 
            {
            

                cout << "Found invalid because " << rules[i].first << "came after " << rules[i].second << endl;
                return 0;
            }
        }
    }

    return v[v.size()/2];
}


int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0;

    vector<pair<int,int> > rules;

    while (getline(MyFile, my_string)) {    
        string s = my_string;
        
        if (s.size() == 0)
        {
            continue;
        }
        else if (s.size() <= 5 )
        {
            readLine(s, rules);
        }

        else
        {
            // check if line is valid
            int middle = checkLine(s, rules);
            total += middle;

            cout << total << endl;
        }

        
    }

    cout << total << endl;
    MyFile.close();
    return 0;
}
