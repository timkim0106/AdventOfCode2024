#include <iostream>
using namespace std;
#include <set>
#include <cstring>
#include <fstream>
#include <sstream>


// for part 2
bool advanced(vector<int> v)
{


    bool valid;
    for (int i = 0; i < v.size(); i++)
    {
        bool valid = true;
        vector<int> copy = v;
        copy.erase(copy.begin() + i);

        vector<int> differences;
        for (int i = 1; i < copy.size(); i++)
        {
            differences.push_back(copy[i] - copy[i-1]);
        }

        // increasing
        if (differences[0] >= 1)
        {
            for (int i = 0; i < differences.size(); i++)
            {
                if (differences[i] < 1 || differences[i] > 3)
                {
                    valid = false;
                }
            }
            
        }

        // decreasing
        else if (differences[0] <= -1)
        {
            for (int i = 0; i < differences.size(); i++)
            {
                if (differences[i] > -1 || differences[i] < -3)
                {
                    valid = false;
                }
            }
        }
        else {
            valid = false;
        
        }

        if (valid == true)
        {
            return true;
        
        }
    }

    return false;
}
int main() {



    //part 2

    ifstream MyFile("input.txt");

    string my_string;

    int safe;

    bool increasing;
    while (getline (MyFile, my_string)) {

        stringstream ss(my_string);

        string s;
        ss >> s;
        int curr = stoi(s);
        
        ss >> s;
        int temp = stoi(s);

        vector<int> v;
        vector<int> differences;
        differences.push_back(curr - temp);
        v.push_back(curr);
        v.push_back(temp);
  

        while (ss >> s)
        {   
            v.push_back(stoi(s));
            curr = temp;
            temp = stoi(s);

            differences.push_back(curr - temp);
        }

        bool clean = true;

        // increasing
        if (differences[0] >= 1)
        {
            for (int i = 1; i < differences.size(); i++)
            {
                if (differences[i] < 1 || differences[i] > 3)
                {
                    // try advanced
                    if (!advanced(v))
                    {
                        clean = false;
                    }
                }
            }
        
        }

        // decreasing
        else if (differences[0] <= -1)
        {
            for (int i = 1; i < differences.size(); i++)
            {
                if (differences[i] > -1 || differences[i] < -3)
                {
                    // try advanced
                    if (!advanced(v))
                    {
                        clean = false;
                    }
                }
            }
            

        }

        else {
            if (!advanced(v))
            {
                clean = false;
            }
        }
        if (clean)
        {
            safe++;
        }

     

    }
    MyFile.close();
// 4 6 5 2 1
// 4 9 3 2 1

    cout << "This many reports are safe: " << safe << endl;

}
