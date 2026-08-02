#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

class ScopeManager {
private:
    vector<map<string, long long>> scopes;

public:
    ScopeManager() {
        scopes.push_back(map<string, long long>());
    }

    void enterScope() {
        scopes.push_back(map<string, long long>());
    }

    void exitScope() {
        if (scopes.size() > 1) {
            scopes.pop_back();
        }
    }

    void declare(const string& name, long long value) {
        scopes.back()[name] = value;
    }

    bool lookup(const string& name, long long& value) {
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].find(name) != scopes[i].end()) {
                value = scopes[i][name];
                return true;
            }
        }
        return false;
    }

    void print(const string& name) {
        long long value;
        if (lookup(name, value)) {
            cout << value << endl;
        } else {
            cout << "UNDEFINED" << endl;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ScopeManager sm;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "{") {
            sm.enterScope();
        } else if (cmd == "}") {
            sm.exitScope();
        } else if (cmd == "DECLARE" || cmd == "declare") {
            string name;
            long long value;
            iss >> name >> value;
            sm.declare(name, value);
        } else if (cmd == "PRINT" || cmd == "print") {
            string name;
            iss >> name;
            sm.print(name);
        }
    }

    return 0;
}
