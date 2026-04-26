PV='/Users/ljx/Desktop/P/github/PowerViolence'
cd $PV

echo 'C Test pvc_add_overflow'

gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_add_overflow.c -o ct_pvc_add_overflow-macos.o -Isrc/PowerViolenceObjects
gcc ct_pvc_add_overflow-macos.o pvc_defines-macos.o -o ct_pvc_add_overflow-macos
./ct_pvc_add_overflow-macos


echo 'C Test pvc_PV_119p8.c'

gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_PV_119p8.c -o pvc_PV_119p8-macos.o
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_PV_119p8.c -o ct_pvc_PV_119p8-macos.o -Isrc/PowerViolenceObjects
gcc pvc_PV_119p8-macos.o ct_pvc_PV_119p8-macos.o pvc_defines-macos.o -o ct_pvc_PV_119p8-macos
./ct_pvc_PV_119p8-macos


echo 'C Test pvc_PV_57p8.c'

gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_PV_57p8.c -o pvc_PV_57p8-macos.o
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_PV_57p8.c -o ct_pvc_PV_57p8-macos.o -Isrc/PowerViolenceObjects
gcc pvc_PV_57p8-macos.o ct_pvc_PV_57p8-macos.o pvc_defines-macos.o -o ct_pvc_PV_57p8-macos
./ct_pvc_PV_57p8-macos
