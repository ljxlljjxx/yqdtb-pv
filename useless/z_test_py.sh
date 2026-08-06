PV=$PV_PATH
return_val=0
cd $PV
rm *-macos

source .venv/bin/activate

echo '更改vertion'
python useless/z_vertion.py

echo 'Python tests'

python setup.py clean --all
pip install --no-cache-dir .
if [ $? -eq 1 ]; then
    return_val=1;
else
    coverage run -m unittest discover tests
    if [[ $? > 0 ]]; then
        return_val=1;
    else
        coverage report -m
        coverage html
    fi
fi


if [ $return_val -eq 1 ]; then
    exit 1
fi
