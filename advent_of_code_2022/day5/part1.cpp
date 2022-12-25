// https://adventofcode.com/2022/day/5

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//             [M] [S] [S]            
//         [M] [N] [L] [T] [Q]        
// [G]     [P] [C] [F] [G] [T]        
// [B]     [J] [D] [P] [V] [F] [F]    
// [D]     [D] [G] [C] [Z] [H] [B] [G]
// [C] [G] [Q] [L] [N] [D] [M] [D] [Q]
// [P] [V] [S] [S] [B] [B] [Z] [M] [C]
// [R] [H] [N] [P] [J] [Q] [B] [C] [F]
//  1   2   3   4   5   6   7   8   9 

int main() {
    ifstream input_file("./input.txt");
    string line;

    // set up initial state of cargos
    vector<char> col1 ({'R','P','C','D','B','G'});
    vector<char> col2 ({'H','V','G'});
    vector<char> col3 ({'N','S','Q','D','J','P','M'});
    vector<char> col4 ({'P','S','L','G','D','C','N','M'});
    vector<char> col5 ({'J','B','N','C','P','F','L','S'});
    vector<char> col6 ({'Q','B','D','Z','V','G','T','S'});
    vector<char> col7 ({'B','Z','M','H','F','T','Q'});
    vector<char> col8 ({'C','M','D','B','F'});
    vector<char> col9 ({'F','C','Q','G'});

    vector<vector<char>> cargos;
    cargos.emplace_back(col1);
    cargos.emplace_back(col2);
    cargos.emplace_back(col3);
    cargos.emplace_back(col4);
    cargos.emplace_back(col5);
    cargos.emplace_back(col6);
    cargos.emplace_back(col7);
    cargos.emplace_back(col8);
    cargos.emplace_back(col9);

    if (input_file.is_open()) {
        int num_move;
        int from;
        int to;
        while (getline(input_file, line)) {
            // move x from col1 to col2
            num_move = stoi(line.substr(line.find("move")+5, line.find("from")-1));
            from = stoi(line.substr(line.find("from")+5, line.find("to")-1));
            to = stoi(line.substr(line.find("to")+3));

            for (auto i = 0; i < num_move; i++) {
                cargos[to-1].push_back(cargos[from-1].back());
                cargos[from-1].pop_back();
            }
        }
    }

    for (auto i = cargos.begin(); i != cargos.end(); i++) {
        cout << i->back() << endl;
    }

    input_file.close();

    return 0;
}