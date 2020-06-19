'''
Problem:

Given an integer k and a string s, find the length of the longest 
substring that contains at most k distinct characters.

For example, given s = "abcba" and k = 2, the longest substring with k 
distinct characters is "bcb".
'''
def numDistinct(s):
    ct = set()
    for letter in s:
        ct.add(s)
    return len(s)

def distinctSub(s, k):
    if len(s) < 1 or k < 1:
        return 0
    leftIdx = 0
    rightIdx = 1
    curr = ''
    letters = 0
    longest = 0
    while (rightIdx <= len(s)):
        # if we see a new letter
        if s[rightIdx-1] not in curr:
            # but we already have max letters
            if letters+1 > k:
                # getting rid of leftmost letter doesn't help us
                if s[leftIdx] in curr[1:]:
                    # remember the longest substring so far
                    if longest < rightIdx-leftIdx-1:
                        longest = rightIdx-leftIdx-1
                    # need to restart from one letter after last occurrence
                    # of leftmost letter
                    leftIdx += curr.rfind(s[leftIdx]) + 1
                    letters = numDistinct(s[leftIdx:rightIdx])
                else:
                    # get rid of leftmost letter
                    leftIdx += 1
            else:
                # keep accumulating letters
                letters += 1 
        curr = s[leftIdx:rightIdx]
        rightIdx += 1
    return max(longest, rightIdx-leftIdx-1)

print(distinctSub("abcba",2))
print(distinctSub("hahahahahah",2))
print(distinctSub("huh",1))
print(distinctSub("Mississippi", 3))



           



