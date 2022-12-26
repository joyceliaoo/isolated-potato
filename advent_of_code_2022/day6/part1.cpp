// https://adventofcode.com/2022/day/6

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ifstream input_file("./input.txt");
    string line;
    unordered_map<char, int> seen; // # of occurences of chars in prev 3 pos
    int start = 0;
    int end = 3;
    if (input_file.is_open()) {
        if (getline(input_file, line)) {
            // add first 3 chars to set
            for (auto i = start; i < end; i++) {
                if (seen.count(line[i]) < 1) {
                    seen[line[i]] = 1;
                } else {
                    seen[line[i]]++;
                }
            }

            while (end < line.length()) {
                // 4th char is unique, found marker
                if (seen.size() == 3 && seen.count(line[end]) < 1) {
                    cout << end+1 << endl;
                    break;
                } else {
                // 4th char not unique, keep moving down the string
                    if (seen[line[start]] == 1) {
                        seen.erase(line[start]);
                    } else {
                        seen[line[start]]--;
                    }

                    if (seen.count(line[end]) < 1) {
                        seen[line[end]] = 1;
                    } else {
                        seen[line[end]]++;
                    }
                    start++;
                    end++;
                }
            }

        }
    }
    input_file.close();

    return 0;
}