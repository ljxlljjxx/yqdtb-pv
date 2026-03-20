clear
for file in test_*.c ../../src/PowerViolenceObjects/*.c
do
    gcc -c $file -o $file.o -O2 -std=c11 -Wall -I ../../src/PowerViolenceObjects -Wno-unused-function
done

gcc main.c *.o ../../src/PowerViolenceObjects/*.o -o main
rm *.o ../../src/PowerViolenceObjects/*.o
./main
//