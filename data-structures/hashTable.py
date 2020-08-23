class hashTable:
    def __init__(self, size, hashFn, eqFn):
        self.table = [ [] for _ in range(size)]
        self.hash = hashFn
        self.eq = eqFn

    def insert(self, key, value):
        idx = self.hash(key)
        curr = self.table[idx]
        for i in range(len(curr)):
            k,v = curr[i]
            if self.eq(k, key): # update an existing key-value pair
                curr[i] = (key,value)
                return ;
        curr.append((key, value))

    def lookup(self, key):
        idx = self.hash(key)
        curr = self.table[idx]
        for k,v in curr:
            if self.eq(k, key):
                return v
        return None

    def delete(self, key):
        idx = self.hash(key)
        curr = self.table[idx]
        for i in range(len(curr)):
            k,v = curr[i]
            if self.eq(k, key):
                del curr[i]
                break
    
    def display(self):
        for i in range(len(self.table)):
            print(i, end=": ")
            print(self.table[i])

tableSize = 10

def myHash(key):
    return hash(key) % tableSize

def myEq(key1, key2):
    return key1 == key2

table = hashTable(tableSize, myHash, myEq)

def test():
    table.insert(1, 'Karma')
    table.insert(28, 'Itona')
    table.insert(11, 'Nagisa')
    table.display()
    assert(table.lookup(11) == 'Nagisa')
    assert(table.lookup(23) == None)
    table.delete(1)
    table.display()

test()



            

        

                
    

