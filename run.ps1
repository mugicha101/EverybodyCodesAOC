param([char]$part='A')
if (Test-Path -Path '../../tmp/code.o') {
    Remove-Item ../../tmp/code.o
}
if (Test-Path -Path '../../tmp/a.exe') {
    Remove-Item ../../tmp/a.exe
}
if (!(Test-Path -Path '../../tmp/main.o')) {
    g++ -O3 -fpermissive -c ../../main.cpp -o ../../tmp/main.o
}
g++ -O3 -fpermissive -c ./code.cpp -o ../../tmp/code.o
g++ ../../tmp/code.o ../../tmp/main.o -o ../../tmp/a.exe
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path '../../tmp/a.exe') {
    ../../tmp/a.exe $part | Tee-Object ./output.txt
}