import urllib.request
import re

curr = "12345"
baseUrl = "http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing="
getNothing = re.compile("the\snext\snothing\sis\s\d+")

for i in range(400):
    if i == 85:
        curr = str(int(curr) / 2)
    else:
        rsp = urllib.request.urlopen(baseUrl+curr)
        content = rsp.read().decode("utf-8")
        try:
            curr = getNothing.search(content)[0].split()[4]
        except:
            print(i, content)
            break
 




