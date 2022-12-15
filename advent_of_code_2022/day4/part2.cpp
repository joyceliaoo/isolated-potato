// https://adventofcode.com/2022/day/4

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input_file("./input.txt");
    string line;
    int num_pairs = 0;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            auto idx = line.find(',');
            auto elf1 = line.substr(0, idx);
            auto elf2 = line.substr(idx+1, line.length());

            auto elf1_idx = elf1.find('-');
            auto elf1_start = stoi(elf1.substr(0, elf1_idx));
            auto elf1_end = stoi(elf1.substr(elf1_idx+1, elf1.length()));
            auto elf2_idx = elf2.find('-');
            auto elf2_start = stoi(elf2.substr(0, elf2_idx));
            auto elf2_end = stoi(elf2.substr(elf2_idx+1, elf2.length()));

            // check if elf1 contains start of elf2
            if (elf1_start <= elf2_start && elf1_end >= elf2_start) {
                num_pairs++;
            } else if (elf1_start <= elf2_end && elf1_end >= elf2_end) {
                // check if elf1 contains end of elf2
                num_pairs++;
            } else if (elf2_start <= elf1_start && elf2_end >= elf1_end) {
                // check if elf2 contains elf1
                num_pairs++;
            }
        }
    }

    input_file.close();
    cout << num_pairs << endl;

    return 0;
}