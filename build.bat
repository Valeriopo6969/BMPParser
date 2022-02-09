clang.exe -o .\bin\example.exe -I .\core\include -I .\SDL2-2.0.20\include\ -L .\SDL2-2.0.20\lib\x64\ .\app\src\example.c  -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32 && .\bin\example.exe
