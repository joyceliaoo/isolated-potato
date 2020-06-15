'''
Problem:
A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.
'''

class Node():
    def __init__(self, val):
        self.data = val
        self.left = None
        self.right = None


def univalCt(root):
    if root == None:
        return 0
    ct = 0
    if root.left != None and root.data == root.left.data:
        ct += 1
    if root.right != None and root.data == root.right.data:
        ct += 1
    if root.left != None and root.right != None and \
            root.left.data == root.data and root.data == root.right.data:
        ct += 1
    return ct + univalCt(root.left) + univalCt(root.right)
    
root = Node(0)
root.left = Node(1)
root.right = Node(0)
root.right.left = Node(1)
root.right.left.left = Node(1)
root.right.left.right = Node(1)
root.right.right = Node(0)
print(univalCt(root))

