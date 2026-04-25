PV='/Users/ljx/Desktop/P/github/PowerViolence'

cd $PV
source $PV/.venv/bin/activate

if [ $? -eq 1 ]; then
    venv
fi

python3 /Users/ljx/Desktop/P/github/PdfToImg/MyPdfToImg.py
echo '规则文件图片生成完成'

$PV/z_test.sh
echo '测试完成'

$PV/z_clean.sh
echo '清理'
