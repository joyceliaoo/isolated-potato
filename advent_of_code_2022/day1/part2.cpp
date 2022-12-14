#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream input_file("./input.txt");
    string line;
    priority_queue<int, vector<int>, greater<int> > top_three;
    int curr = 0;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            // check if we are starting count for a new reindeer
            if (line == "") {
                // update top 3 values
                top_three.push(curr);
                if (top_three.size() > 3) {
                    top_three.pop();
                }
                
                curr = 0;
            } else { // otherwise keep count for current reindeer
                curr += stoi(line);
            }
        }
    }

    input_file.close();
    assert(top_three.size() == 3);
    int res = 0;
    while (!top_three.empty()) {
        res += top_three.top();
        top_three.pop();
    }
    cout << res << endl;

    return 0;
}