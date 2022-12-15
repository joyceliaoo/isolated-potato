// https://adventofcode.com/2022/day/3

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    ifstream input_file("./input.txt");
    string line;
    string item_types = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int priorities = 0;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            int num_items = line.length();
            // build hash map for items in first compartment
            unordered_set<char> comp1_items;
            for (int i = 0; i < num_items / 2; i++) {
                comp1_items.insert(line[i]);
            }

            // find repeated item in second compartment
            for (int i = num_items / 2; i < num_items ; i++) {
                if (comp1_items.count(line[i]) > 0) {
                    priorities += (item_types.find(line[i]) + 1);
                    break;
                }
            }
        }
    }

    input_file.close();
    cout << priorities << endl;

    return 0;
}