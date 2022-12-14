// https://adventofcode.com/2022/day/1

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input_file("./input.txt");
    string line;
    int max = 0;
    int curr = 0;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            // check if we are starting count for a new reindeer
            if (line == "") {
                // update max seen so far
                if (curr > max) {
                    max = curr;
                }
                curr = 0;
            } else { // otherwise keep count for current reindeer
                curr += stoi(line);
            }
        }
    }

    input_file.close();
    cout << max << endl;

    return 0;
}