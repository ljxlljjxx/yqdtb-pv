PV='/Users/ljx/Desktop/P/github/PowerViolence'
return_val=0
cd $PV
rm *-macos

echo '更改vertion'
python -c '
with open("setup.py") as f:
    a = f.read().splitlines()
b = []
for i in a:
    if i.startswith("version = "):
        x = int(i.split(".")[-1][:-1])
        x += 1
        b.append(".".join(i.split(".")[:-1]) + "." + str(x) + "\"")
    else:
        b.append(i)
with open("setup.py", "w") as f:
    f.write("\n".join(b))
'

echo 'Python tests'

source .venv/bin/activate
python setup.py clean --all
pip install --no-cache-dir .
if [ $? -eq 1 ]; then
    return_val=1;
else
    echo 'Python test'
    python -m unittest discover tests
    if [[ $? > 0 ]]; then
        return_val=1;
    fi
fi


if [ $return_val -eq 1 ]; then
    exit 1
fi
