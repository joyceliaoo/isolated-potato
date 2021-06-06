def rev(n,c):
    if c < n-1:
        return "IMPOSSIBLE"
    og = [i for i in range(1,n+1)]
    excess = c - (n-1)
    dist = []
    for i in reversed(range(n)):
        if excess <= i:
            dist.append(excess+1)
            excess = 0
            break
        excess -= i
        dist.append(i+1)
    if excess > 0:
        return "IMPOSSIBLE"
    print(dist)
    
    for i in reversed(range(len(dist))):
        front = og[:i]
        mid = og[i:i+dist[i]][::-1]
        back = og[i+dist[i]:]
        og = front + mid + back
    
    og = [str(x) for x in og]
    return " ".join(og)

num_tests = int(input())
for t in range(num_tests):
    line = input().split(" ")
    n = int(line[0])
    c = int(line[1])
    res = rev(n,c)
    print("Case #" + str(t+1) + ": " + res)
    
