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

        // Trim
        size_t start = line.find_first_not_of(" \t");
        if (start == string::npos) continue;
        line = line.substr(start);

        if (line[0] == '{') {
            sm.enterScope();
        } else if (line[0] == '}') {
            sm.exitScope();
        } else if (line.find("int ") == 0) {
            // Parse: int x = value
            size_t eqPos = line.find('=');
            if (eqPos != string::npos) {
                string namePart = line.substr(4, eqPos - 4);
                // Trim name
                size_t ns = namePart.find_first_not_of(" \t");
                size_t ne = namePart.find_last_not_of(" \t");
                string name = namePart.substr(ns, ne - ns + 1);

                string valuePart = line.substr(eqPos + 1);
                long long value = stoll(valuePart);
                sm.declare(name, value);
            }
        } else if (line.find("print(") == 0) {
            // Parse: print(x)
            size_t start = line.find('(');
            size_t end = line.find(')');
            if (start != string::npos && end != string::npos) {
                string name = line.substr(start + 1, end - start - 1);
                long long value;
                if (sm.get(name, value)) {
                    cout << value << endl;
                } else {
                    cout << 0 << endl;
                }
            }
        }
    }

    return 0;
}
