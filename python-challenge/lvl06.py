import re
import zipfile

folder = "channel/"
curr = "90052"
ext = ".txt"
num = re.compile("\d+")
zippedList = zipfile.ZipFile("channel.zip", "r")
c = ""

while True:
    c += zippedList.getinfo(curr+ext).comment.decode("utf-8")
    with open(folder+curr+ext, 'r') as f:
        content = f.read()
        try:
            curr = num.search(content)[0]
        except:
            print("breakpt", content)
            break

print(c)
