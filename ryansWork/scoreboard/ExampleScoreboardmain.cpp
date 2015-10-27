#include "Scoreboard.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
 
string getInput () {
    static char input_char[256];
    cin.getline(&input_char[0], 256, '\n');
    return string(input_char);
}
int str2int (string str) {
    istringstream ss(str);
    int result = 0;
    ss >> result;
    return result;
}
int main () {
    Scoreboard s;
    string input;
   
    while (input != "exit") {
        cout << "Command: ";
        input = getInput();
 
        if (input == "load") {
            cout << "Data File: ";
            input = getInput();
            s.load(input.c_str());
        } else if (input == "save") {
            cout << "Data File: ";
            input = getInput();
            s.save(input.c_str());
        } else if (input == "add") {
            Scoreboard::Entry entry;
            cout << "Name: ";
            entry.setName(getInput());
            cout << "Score: ";
            entry.score = str2int(getInput());
            int pos = s.addEntry(entry);
            cout << "Entry was added at position #" << pos << "\n";
        } else if (input == "scores") {
            for (int i=0; i<s.size(); ++i) {
                Scoreboard::Entry e = s.getEntry(i);
                cout << e.name << "\t-\t" << e.score << endl;
            }
        } else if (input == "prune") {
            int max = str2int(getInput());
            s.prune(max);
        } else if (input == "size") {
            cout << "Size = " << s.size() << endl;
        }
    }
    return 0;
}
