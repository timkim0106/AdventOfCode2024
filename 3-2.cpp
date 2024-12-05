#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool isMulFunctionStart(const string& s, int pos) {
    return (pos + 4 <= s.size()) && (s.substr(pos, 3) == "mul") && (s[pos + 3] == '(');
}


bool extractInteger(const string& s, int start, int& number, int& endPos) {
    int i = start;
    number = 0;
    if (i >= s.size() || !isdigit(s[i])) {
        return false;
    }
    while (i < s.size() && isdigit(s[i])) {
        number = number * 10 + (s[i] - '0');
        i++;
    }
    endPos = i;
    return true;
}

int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0;
    int n = 0;
    bool toDo = true; 

    while (getline(MyFile, my_string)) {
    
        string s = my_string;
        int pos = 0;

        while (pos < s.size())
        {
        
            while (toDo && pos < s.size()) {
               
                size_t dontPos = s.find("don't()", pos);
                size_t doPos = s.find("do()", pos);
                size_t mulPos = s.find("mul(", pos);

                // Handle "don't()" before "mul("
                if (dontPos != string::npos && (mulPos == string::npos || dontPos < mulPos)) {
                  
                    toDo = false;
                    break;
                }

                // Handle "do()" before "mul("
                if (doPos != string::npos && (mulPos == string::npos || doPos < mulPos)) {
                    
                    pos = doPos + 4; // Length of "do()" is 4
                    continue;
                }

                // If no "mul(" found, stop processing
                if (mulPos == string::npos) {
                    break;
                }

                // Check if "mul(" is a valid function call
                if (isMulFunctionStart(s, mulPos)) {
                    // Extract first number after "mul("
                    int n1 = 0;
                    int endPos1 = 0;
                    if (!extractInteger(s, mulPos + 4, n1, endPos1)) {
                        
                        pos = mulPos + 3; // Move past "mul"
                        continue;
                    }

                    // After the first number, expect a comma
                    if (endPos1 >= s.size() || s[endPos1] != ',') {
                        pos = mulPos + 3; // Move past "mul"
                        continue;
                    }

                    // Extract second number after comma
                    int n2 = 0;
                    int endPos2 = 0;
                    if (!extractInteger(s, endPos1 + 1, n2, endPos2)) {
                        pos = mulPos + 3; // Move past "mul"
                        continue;
                    }

                    // After the second number, expect a closing parenthesis ')'
                    if (endPos2 >= s.size() || s[endPos2] != ')') {
                        pos = mulPos + 3; // Move past "mul"
                        continue;
                    }

                    // Valid "mul(n1,n2)" found
                    cout << "Found mul(" << n1 << "," << n2 << ") -> Product: " << (n1 * n2) << endl;
                    total += n1 * n2;

                    // Move past the current "mul(n1,n2)"
                    pos = endPos2 + 1;
                } else {
                    // "mul" found but not followed by '('
                    pos = mulPos + 3; // Move past "mul"
                }
            }

            // "do()" commands after "don't()" 
            while (!toDo && pos < s.size()) {
                size_t doPos = s.find("do()", pos);
                if (doPos != string::npos) {
                    pos = doPos + 4; // Skip past "do()"
                    toDo = true;
                } else {
                    pos = s.size(); // to exit this loop and move on to next line
                    break;
                }
            }
        }

        cout << "Current total after line " << n << ": " << total << endl << endl;
    }

    cout << "Final Total Product: " << total << endl;
    MyFile.close();
    return 0;
}
