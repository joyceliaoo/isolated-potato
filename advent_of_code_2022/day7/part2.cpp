// https://adventofcode.com/2022/day/7

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class Dir {
    public:
        Dir(string dir_name): name(dir_name) {}
        string name;
        unordered_map<string, shared_ptr<Dir> > subdirs;
        shared_ptr<Dir> parent = nullptr;
        size_t size = 0;
        size_t ls = 0;
};

// DFS on file tree to get dir sizes
size_t get_size(size_t &smallest, shared_ptr<Dir> curr, size_t &threshold) {
    // leaf dir, return size directly
    if (curr->subdirs.size() == 0) {
        if (curr->size >= threshold && curr->size < smallest) {
            cout << curr->name << " has size " << curr->size << endl;
            smallest = curr->size;
        }
        return curr->size;
    }

    size_t subdirs_size = 0;
    // add up size of all subdirs
    for (auto it = curr->subdirs.begin(); it != curr->subdirs.end(); it++) {
        auto subdir_size = get_size(smallest, it->second, threshold);
        subdirs_size += subdir_size;
    }

    auto total_size = curr->size + subdirs_size;

    if (total_size >= threshold && total_size < smallest) {
        cout << curr->name << " has size " << total_size << endl;
        smallest = total_size;
    }
    return total_size;
}

int main() {
    ifstream input_file("./input.txt");
    string line;
    shared_ptr<Dir> root = make_shared<Dir>("/");
    shared_ptr<Dir> curr = root;
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            // cd
            if (line[0] == '$' && line.find("cd") != string::npos) {
                // go to prev dir by tracing parent ptr
                if (line.substr(line.find("cd")+3) == "..") {
                    curr = curr->parent;
                    cout << "dir changed to prev level " << curr->name << endl;
                } else {
                    string target_dir = line.substr(line.find("cd")+3);
                    assert(curr->subdirs.count(target_dir) > 0);
                    curr = (curr->subdirs)[target_dir];
                    cout << "dir changed to " << curr->name << endl;
                }
                continue;
            }

            // ls 
            if (line[0] == '$' && line.find("ls") !=  string::npos) {
                curr->ls++;
                cout << "listing files in " << curr->name << endl;
                continue;
            }

            // dir in ls
            // add dir to subdirs of current dir
            if (line.substr(0,3) == "dir") {
                auto new_dir_name = line.substr(4);
                // make a new obj to represent the subdir listed
                // in ls if we haven't already
                if (curr->subdirs.count(new_dir_name) == 0) {
                    auto new_dir = make_shared<Dir>(new_dir_name);
                    new_dir->parent = curr;
                    (curr->subdirs).insert({new_dir_name, new_dir});
                    cout << line.substr(4) << " is a subdirectory of " << curr->name << endl;
                }
                continue;
            }

            // file in curr_dir
            // tally size if we haven't performed ls on current dir
            if (curr->ls <= 1) {
                curr->size += stoi(line.substr(0, line.find(' ')));
                 cout << "current dir " << curr->name << " has file of size " << stoi(line.substr(0, line.find(' '))) << " new total size is " << curr->size << endl;
            }
        }
    }

    input_file.close();

    size_t disk_space = 70000000;
    size_t update_space = 30000000;
    size_t res = disk_space;
    size_t threshold = 0;
    auto used_space = get_size(res, root, threshold);
    cout << "disk space " << disk_space << endl; 
    threshold = update_space - (disk_space - used_space);
    cout << "threshold " <<  threshold << endl;
    res = disk_space;
    get_size(res, root, threshold);
    cout << res << endl;

    return 0;
}