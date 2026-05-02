PV='/Users/ljx/Desktop/P/github/PowerViolence'

cd $PV

if [[ $1 == "-T" ]]; then
    echo '跳过规则文件图片生成'
else
    if [ -f $PV/.venv/bin/activate ]; then
        source $PV/.venv/bin/activate
    else
        venv
    fi
    python3 /Users/ljx/Desktop/P/github/PdfToImg/MyPdfToImg.py
    echo '规则文件图片生成完成'
fi

$PV/useless/z_clean.sh
echo '清理'

$PV/useless/z_test.sh
if [ $? -eq 1 ]; then
    echo '测试未通过';
    exit 1
fi

echo '测试完成'
