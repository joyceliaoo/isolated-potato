# cons(a, b) constructs a pair, and car(pair) and cdr(pair) 
# returns the first and last element of that pair. 
# For example, car(cons(3, 4)) returns 3, and cdr(cons(3, 4)) returns 4.

# Given this implementation of cons:

def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair

# Implement car and cdr.

def car(pair_fun):
    def first(a,b):
        return a
    return pair_fun(first)

def cdr(pair_fun):
    def last(a,b):
        return b
    return pair_fun(last)

print(car(cons("hi", "hello")))
print(cdr(cons("hi", "hello")))
print(car(cons(1, "hello")))
    
