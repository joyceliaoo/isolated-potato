// https://adventofcode.com/2022/day/2


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// A -> rock, B -> paper, C -> scissors
// X -> rock (+1), Y -> paper (+2), Z -> scissors (+3)

int getIdx(string s) {
    if (s == "A" || s == "X") {
        return 0;
    }
    if (s == "B" || s == "Y") {
        return 1;
    }
    if (s == "C" || s == "Z") {
        return 2;
    }

    return -1;
}

auto main() -> int {
    // col1: A 
    // col2: X, Y, Z
    vector<int> rock_points = {4, 8, 3};

    // col1: B
    // col2: X, Y, Z
    vector<int> paper_points = {1, 5, 9};

    // col1: C
    // col2: X, Y, Z
    vector<int> scissors_points = {7, 2, 6};
    vector<vector<int>> points;
    points.emplace_back(rock_points);
    points.emplace_back(paper_points);
    points.emplace_back(scissors_points);
    int score = 0;

    ifstream input_file("./input.txt");
    string line;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            string col1 = line.substr(0,1);
            string col2 = line.substr(2,3);
            score += points[getIdx(col1)][getIdx(col2)];
        }
    }

    input_file.close();
    cout << score << endl;

    return 0;
}