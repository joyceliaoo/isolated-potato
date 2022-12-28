// https://adventofcode.com/2022/day/7

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int get_sizes(string dir_name, unordered_map<string,int> &total_sizes,
               unordered_map<string, vector<string>> &file_tree,
               unordered_map<string, int> &file_sizes) 
{
    if (file_tree.count(dir_name) < 1) {
        cout << dir_name << " is leaf dir " << endl;
        auto file_size = file_sizes.count(dir_name) < 1 ? 0 : file_sizes[dir_name];
        total_sizes.insert({dir_name, file_size});
        return total_sizes[dir_name];
    }

    int subdirs_size = 0;
    cout << "finding subdirs of " << dir_name << endl;
    auto it = file_tree.find(dir_name);
    for (auto subdir: it->second) {
        cout << "subdir " << subdir  << " of " << dir_name << endl;
        auto subdir_size = get_sizes(subdir, total_sizes, file_tree, file_sizes);
        cout << "got size " << subdir_size << " for subdir " << subdir << endl;
        subdirs_size += subdir_size;
    }

    auto file_size = file_sizes.count(dir_name) < 1 ? 0 : file_sizes[dir_name];
    int total_size = file_size + subdirs_size;
    cout << "total size for " << dir_name << " is " << total_size << endl;
    total_sizes[dir_name] = total_size;
    return total_size;
}

int main() {
    ifstream input_file("./input.txt");
    string line;
    unordered_map<string, vector<string>> file_tree;
    unordered_map<string, int> file_sizes;
    unordered_map<string, string> parent_dir;
    string curr_dir = "/";
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            // cd
            if (line[0] == '$' && line.find("cd") != string::npos) {
                if (line.substr(line.find("cd")+3) == "..") {
                    curr_dir = parent_dir[curr_dir];
                    cout << "dir changed to prev level " << curr_dir << endl;
                } else {
                    curr_dir = line.substr(line.find("cd")+3);
                    cout << "dir changed to " << curr_dir << endl;
                }
                continue;
            }

            // ls 
            if (line[0] == '$' && line.find("ls") !=  string::npos) {
                cout << "listing files in " << curr_dir << endl;
                continue;
            }

            // dir in ls
            // add dir under curr_dir
            if (line.substr(0,3) == "dir") {
                file_tree[curr_dir].push_back(line.substr(4));
                parent_dir[line.substr(4)] = curr_dir;
                cout << line.substr(4) << " is a subdirectory of " << curr_dir << endl;
                continue;
            }

            // file in curr_dir
            file_sizes[curr_dir] += stoi(line.substr(0, line.find(' ')));
            cout << "curr_dir " << curr_dir << " has file of size " << stoi(line.substr(0, line.find(' '))) << " new total size is " << file_sizes[curr_dir] << endl;
        }
    }

    input_file.close();

    unordered_map<string,int> dir_total_sizes;
    get_sizes("/", dir_total_sizes, file_tree, file_sizes);
    int res = 0;
    for (auto it = dir_total_sizes.begin(); it != dir_total_sizes.end(); it++) {
        cout << it->first << "has size " << it->second << endl;
        if (it->second <= 100000) {
            res += it->second;
        }
    }

    cout << res << endl;

    return 0;
}