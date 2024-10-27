#include "headers.h"

vector<string> History;
string historyFileName = "/home/vaishnavi/2023201029_Assignment2/history.txt";
const int maxSize = 20;  

void loadHistory() {
    ifstream historyFile(historyFileName);
    if (historyFile.is_open()) {
        string line;
        while (getline(historyFile, line)) {
            cout << line << endl;
        }
        historyFile.close();
    }
}

void loadHistory(int n) {
    ifstream historyFile(historyFileName);
    if (historyFile.is_open()) {
        vector<string> ncommands;
        string line;
        while (getline(historyFile, line)) {
            ncommands.push_back(line);
            if (ncommands.size() > n) {
                ncommands.erase(ncommands.begin());
            }
        }

        for (const string& command : ncommands) {
            cout << command << endl;
        }

        historyFile.close();
    }
}

void storehistory1(string command1) {
    History.push_back(command1);
     while (History.size() > maxSize) {
        History.erase(History.begin());
    }

    ofstream historyFile(historyFileName);
    if (historyFile.is_open()) {
    for (const string& command : History) {
            historyFile << command << endl;
        }
        historyFile.close();
    }
}




 
