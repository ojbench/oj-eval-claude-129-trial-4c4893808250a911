#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

class ScopeManager {
private:
    vector<map<string, int>> scopes;

public:
    ScopeManager() {
        scopes.push_back(map<string, int>());
    }

    void enterScope() {
        scopes.push_back(map<string, int>());
    }

    void exitScope() {
        if (scopes.size() > 1) {
            scopes.pop_back();
        }
    }

    void set(const string& name, int value) {
        scopes.back()[name] = value;
    }

    bool get(const string& name, int& value) {
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].find(name) != scopes[i].end()) {
                value = scopes[i][name];
                return true;
            }
        }
        return false;
    }
};

int main() {
    ScopeManager sm;
    string line;

    while (getline(cin, line)) {
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "enter") {
            sm.enterScope();
        } else if (cmd == "exit") {
            sm.exitScope();
        } else if (cmd == "set") {
            string name;
            int value;
            iss >> name >> value;
            sm.set(name, value);
        } else if (cmd == "get") {
            string name;
            iss >> name;
            int value;
            if (sm.get(name, value)) {
                cout << value << endl;
            } else {
                cout << "undefined" << endl;
            }
        }
    }

    return 0;
}
