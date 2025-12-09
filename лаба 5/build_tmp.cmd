call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /std:c++17 /utf-8 /EHsc /Iinclude src\*.cpp src\sqlite3.c /Fe:lab6.exe
