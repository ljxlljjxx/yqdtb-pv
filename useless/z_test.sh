PV='/Users/ljx/Desktop/P/github/PowerViolence'
return_val=0
cd $PV
rm *-macos

if [[ $2 == "-c" ]]; then
    useless/z_test_py.sh
    exit $?
elif [[ $2 == "-py" ]]; then
    useless/z_test_c.sh
    exit $?
fi

echo 'Python tests'

useless/z_test_c.sh
if [ $? -eq 1 ]; then
    return_val=1
fi

useless/z_test_py.sh
if [ $? -eq 1 ]; then
    return_val=1
fi


if [ $return_val -eq 1 ]; then
    exit 1
fi
