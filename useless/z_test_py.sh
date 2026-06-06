PV='/Users/ljx/Desktop/P/github/PowerViolence'
return_val=0
cd $PV
rm *-macos

echo '更改vertion'
python -c '
def change_file(file_name):
    with open(file_name) as f:
        a = f.read().splitlines()
    b = []
    for i in a:
        if i.startswith("version = ") or i.startswith("__version__ = "):
            x = int(i.split(".")[-1][:-1])
            x += 1
            b.append(".".join(i.split(".")[:-1]) + "." + str(x) + "\"")
        elif i.startswith("DEBUG = "):
            b.append("DEBUG = True")
        else:
            b.append(i)
    with open(file_name, "w") as f:
        f.write("\n".join(b))
change_file("setup.py")
change_file("src/PowerViolenceObjects/__init__.py")
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
