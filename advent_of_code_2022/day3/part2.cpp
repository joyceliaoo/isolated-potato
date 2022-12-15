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
    unordered_set<char> elf1_items;
    unordered_set<char> elf2_items;
    int elf_num = 1;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            // create set for all items carried by first elf
            if (elf_num % 3 == 1) { 
                for (int i = 0; i < line.length(); i++) {
                    elf1_items.insert(line[i]);
                }
            } else if (elf_num % 3 == 2) {  // create set for all items carried by second elf
                for (int i = 0; i < line.length(); i++) {
                    elf2_items.insert(line[i]);
                }
            } else {
                // check items carried by third elf against previous two elves
                for (int i = 0; i < line.length(); i++) {
                    if (elf1_items.count(line[i]) > 0 && elf2_items.count(line[i]) > 0) {
                        priorities += item_types.find(line[i]) + 1;
                        elf1_items.clear();
                        elf2_items.clear();
                        break;
                    }
                }
            }
            elf_num++;
        }
    }

    input_file.close();
    cout << priorities << endl;

    return 0;
}