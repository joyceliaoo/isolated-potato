'''
Problem:
Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, 
count the number of ways it can be decoded.

For example, the message '111' would give 3, since it could be 
decoded as 'aaa', 'ka', and 'ak'.

You can assume that the messages are decodable. 
For example, '001' is not allowed.
'''

# length of longest encoding that a letter has
MAX_ENC_LEN = 2

def numDec(msg):
    if len(msg) <= 1:
        return 1
    res = 0
    for i in range(1, MAX_ENC_LEN+1): 
        # if we can break msg at this index
        if 0 < int(msg[0:i]) < 27:
            res += numDec(msg[i:])
    return res

print("111 can be decoded in", numDec("111"), "ways")
print("11 can be decoded in", numDec("11"), "ways")
print("2561 can be decoded in", numDec("2561"), "ways")
print("1234 can be decoded in", numDec("1234"), "ways")
print("1111 can be decoded in", numDec("1111"), "ways")
print("222222222 can be decoded in", numDec("222222222"), "ways")
