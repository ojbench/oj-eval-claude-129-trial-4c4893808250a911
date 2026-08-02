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
        // Declare in current scope
        scopes.back()[name] = value;
    }

    bool assign(const string& name, long long value) {
        // Assign to existing variable (search from inner to outer)
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].find(name) != scopes[i].end()) {
                scopes[i][name] = value;
                return true;
            }
        }
        return false;  // Variable not found
    }

    bool get(const string& name, long long& value) {
        for (int i = scopes.size() - 1; i >= 0; i--) {
            auto it = scopes[i].find(name);
            if (it != scopes[i].end()) {
                value = it->second;
                return true;
            }
        }
        return false;
    }
};

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) {
        return 0;
    }
    cin.ignore();

    ScopeManager sm;

    for (int i = 0; i < n; i++) {
        string line;
        if (!getline(cin, line)) break;

        line = trim(line);
        if (line.empty()) {
            i--;
            continue;
        }

        // Remove semicolon if present
        if (!line.empty() && line.back() == ';') {
            line.pop_back();
            line = trim(line);
        }

        if (line == "{") {
            sm.enterScope();
        } else if (line == "}") {
            sm.exitScope();
        } else if (line.find("int ") == 0) {
            // Parse: int x = value (declaration)
            size_t eqPos = line.find('=');
            if (eqPos != string::npos) {
                string namePart = line.substr(4, eqPos - 4);
                namePart = trim(namePart);

                string valuePart = line.substr(eqPos + 1);
                valuePart = trim(valuePart);

                try {
                    long long value = stoll(valuePart);
                    sm.declare(namePart, value);
                } catch (...) {
                }
            }
        } else if (line.find('=') != string::npos && line.find("int ") != 0) {
            // Parse: x = value (assignment)
            size_t eqPos = line.find('=');
            string namePart = line.substr(0, eqPos);
            namePart = trim(namePart);

            string valuePart = line.substr(eqPos + 1);
            valuePart = trim(valuePart);

            try {
                long long value = stoll(valuePart);
                sm.assign(namePart, value);
            } catch (...) {
            }
        } else if (line.find("print(") != string::npos) {
            // Parse: print(x)
            size_t start = line.find('(');
            size_t end = line.find(')');
            if (start != string::npos && end != string::npos) {
                string name = line.substr(start + 1, end - start - 1);
                name = trim(name);
                long long value;
                if (sm.get(name, value)) {
                    cout << value << endl;
                }
            }
        }
    }

    return 0;
}
