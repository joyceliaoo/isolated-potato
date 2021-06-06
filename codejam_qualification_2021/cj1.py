num_tests = int(input())

def revCost (arr):
    inorder = sorted(arr)
    cost = 0
    temp = arr
    for i in range(len(arr)-1):
        min_idx = temp.index(inorder[i], i, len(arr))
        cost += min_idx-i+1
        front = temp[:i]
        middle = temp[i:min_idx+1][::-1]
        back = temp[min_idx+1:]
        temp = front + middle + back
    return cost

for t in range(num_tests):
    num_ele = int(input())
    lst = input().split(" ")
    lst = [int(x) for x in lst]
    cost = revCost(lst)
    print("Case #" + str(t) + ": " + str(cost))

