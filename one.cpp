#include <iostream>
using namespace std;
#include <set>
#include <cstring>
#include <fstream>
#include <sstream>

int main() {


    // part 1

    ifstream MyFile("input.txt");

    string my_string;

    int safe;

    bool increasing;
    while (getline (MyFile, my_string)) {

        stringstream ss(my_string);
        bool valid = true;
        bool allowed = true;

        int same;
        string s;
        ss >> s;
        int curr = stoi(s);
        ss >> s;
        int temp = stoi(s);
        if ((curr - temp > 0) && abs(curr - temp) <= 3)
        {
            increasing = true;
        }
        else if ((curr - temp < 0) && abs(curr - temp) <= 3)
        {
            increasing = false;
        }

        while (ss >> s)
        {   
            curr = temp;
            temp = stoi(s);
            if (increasing == true && (curr - temp > 0) && abs(curr - temp) <= 3)
            {
            }
            else if (increasing == false && (curr - temp < 0) && abs(curr - temp) <= 3)
            {
            }
            else
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            safe++;
        }

    }
    MyFile.close();


    cout << "This many reports are safe: " << safe << endl;

}