from PIL import Image, ImageFilter

im = Image.open("oxygen.png")

s = []

for i in range(im.size[0]):
    s.append(im.getpixel((i,im.size[1]/2))[0])

distinct = []

for num in s:
    if distinct == [] or distinct[-1] != num:
        distinct.append(num)

w = ""

for num in distinct:
    w += chr(num)

print(w)

ans = [105, 10, 16, 101, 103, 14, 105, 16, 121]

for num in ans:
    print(chr(num))

