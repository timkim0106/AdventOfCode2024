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

    int total;
    vector<int> total1;
    vector<int> total2;

  
    while (getline (MyFile, my_string)) {


        string str1, str2;
        stringstream s(my_string);
        s >> str1 >> str2;

        int n1 = stoi(str1);
        int n2 = stoi(str2);

        total1.push_back(n1);
        total2.push_back(n2);
    
    }

    MyFile.close(); 

    sort(total1.begin(), total1.end());
    sort(total2.begin(), total2.end());
    for (int i = 0; i < total1.size(); i++)
    {
        total += abs(total1[i] - total2[i]);
    }


    cout << "This is total difference: " << total << endl;



    // part 2 

    int score = 0;

    for (int i = 0; i < total1.size(); i++)
    {

        int n = 0;

        for (int j = 0; j < total2.size(); j++)
        {
            if (total1[i] == total2[j])
            {
                n++;
            }
            else if (total1[i] < total2[j])
            {
                break;
            }
        }

        score += n * total1[i];
    }
    cout << "this is total score: " << score << endl;
}