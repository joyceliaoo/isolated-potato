'''
Suppose we represent our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.
'''
DIR = 0
FILE = 1

def findLongest(path):
    if "." not in path:
        return 0
    lines = path.split("\n")
    currLvl = -1
    longest = 0
    longestDir = ""
    currDir = ""
    prev = DIR
    for line in lines:
        lvl = line.count("\t")
        # files/dirs in the same level
        if lvl == currLvl:
            if prev == DIR:
                # get rid of dir immediately above in same level
                currDir = "/".join(currDir.split("/")[:-2]) + "/"
        elif lvl < currLvl: # going back to an upper level
            diff = currLvl - lvl 
            if prev == DIR:
                diff += 1
            currDir = "/".join(currDir.split("/")[:-diff-1]) + "/"
        currLvl = lvl
        # a file
        if "." in line:
            longest = max(longest, len(currDir)+len(line.strip("\t")))
            prev = FILE
        else: # a dir
            currDir += line.strip("\t") + "/"
            prev = DIR
    return longest

print(findLongest("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"))
print(findLongest("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"))

            

            







