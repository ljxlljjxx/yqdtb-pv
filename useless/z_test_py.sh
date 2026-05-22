PV='/Users/ljx/Desktop/P/github/PowerViolence'
return_val=0
cd $PV
rm *-macos

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
