
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;


// check for open parenth, string starts with "mul"
bool check1(string s)
{
    if (s.size() >= 4 && s[3] == '(')
    {
        return true;
    }
    return false;

}

// check for comma, string starts with "mul("
bool check2(string s)
{
    int index = 5;
    while (isdigit(s[index]))
    {
        index++;
    }

    if (s[index] == ',')
    {
        return true;
    }

    return false;
    
    
}
// check for closing parenth, string starts with "mul(XXX,"
// index is index of comma + 2
bool check3(string s, int index)

{

    while (isdigit(s[index]))
    {
        index++;
    }
    if (s[index] == ')')
    {
        return true;
    }
    return false;
}


int main() {

    // part 1

    ifstream MyFile("input.txt");

    string my_string;

    int total;

    while (getline (MyFile, my_string)) {

        string s = my_string;

        
        
        int i = s.find("mul");
        
        while (i != string::npos)
        {
            s = s.substr(i);
            if (check1(s))
            {
                if (check2(s))
                {
                  
                    int commaIndex = s.find(",");
                    
                    if (check3(s, commaIndex + 2))
                    {
                        int closeParenthIndex = s.find(')');
                        int n1 = stoi(s.substr(4, commaIndex - 4));
                        int n2 = stoi(s.substr(commaIndex + 1, closeParenthIndex - commaIndex - 1));
                        cout << "n1: " << n1 << endl;
                        cout << "n2: " << n2 << endl;
                        int product = n1 * n2;
                        total += product;
                    }

                }
            }

            // to go to find next occurance of "mul"
            s = s.substr(1);
            i = s.find("mul");
            
            
        }



    }
    cout << "this is total: " << total << endl;
}
