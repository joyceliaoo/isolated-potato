'''
A builder is looking to build a row of N houses that can be of K different colors. He has a goal of minimizing cost while ensuring that no two neighboring houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to build the nth house with kth color, return the minimum cost which achieves this goal.
'''

def minCost(costs):
    # N = 1
    if type(costs[0])!= list:
        return min(costs)
    N = len(costs)
    K = len(costs[0])
    # only 1 color, more than 1 house
    if K == 1:
        return -1
    # costs up until current house
    prevColors = costs[0]
    for house in range(1, N):
        curr = costs[house]
        temp = [None] * K
        for color in range(K):
            # total cost after applying color for previous house
            prevCost = prevColors[color]
            # has to be a diff color than previous house
            options = curr[:color]+curr[color+1:]
            # choose best color
            currChoice = curr.index(min(options))
            if temp[currChoice] == None:
                temp[currChoice] = prevCost + curr[currChoice]
            else:
                # take the smallest cost for repeated choices
                temp[currChoice] = \
                        min(temp[currChoice], prevCost + curr[currChoice])
        prevColors = temp

    return min([ x for x in prevColors if x != None])

costs0 = [2, 3, 4]
print(minCost(costs0))
costs1 = [[1,2,3],[4,5,6]]
print(minCost(costs1))

   
