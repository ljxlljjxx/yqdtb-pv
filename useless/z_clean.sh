rm *.o
rm *-macos

python -c '
with open("setup.py") as f:
    a = f.read().splitlines()
b = []
for i in a:
    if i.startswith("DEBUG = "):
        b.append("DEBUG = False")
    else:
        b.append(i)
with open("setup.py", "w") as f:
    f.write("\n".join(b))
'
