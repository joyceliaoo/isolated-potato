def minCost(x,y,s):
    if len(s) < 2:
        return 0
    res = 0
    if s[:2] == "JC":
        res += y
    elif s[:2] == "CJ":
        res += x
    i = 1
    while i < len(s)-1:
        if s[i] == "?":
            nextC = s.find("C",i+1)
            nextJ = s.find("J",i+1)
            nextFixed = -1
            if nextC == -1 and nextJ == -1:
                break
            elif  nextC == -1:
                nextFixed = nextJ
            elif  nextJ == -1:
                nextFixed = nextC
            else:
                nextFixed = min(nextC,nextJ)
            if s[i-1] == "C" and s[nextFixed] == "J":
                res += x
            elif s[i-1] == "J" and s[nextFixed] == "C":
                res += y
            i = nextFixed
        elif  s[i] == "J" and s[i+1] == "C":
            res += y
            i += 1
        elif  s[i] == "C" and s[i+1] == "J":
            res += x
            i += 1
        else:
            i += 1
    return res
   
                                            
num_tests = int(input())
for t in range(num_tests):
    line = input().split(" ")
    x = int(line[0])
    y = int(line[1])
    s = line[2]

    cost = minCost(x,y,s)

    print("Case #" + str(t+1) + ": " + str(cost))
            

