import pickle

src = open("banner.p", "rb")
p = pickle.load(src)

s = ""

for lst in p:
    for pair in lst:
        for i in range(pair[1]):
            s += pair[0]

print(s)

