@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
if %errorlevel% neq 0 exit /b %errorlevel%
if not exist obj\debug mkdir obj\debug
if not exist bin\debug mkdir bin\debug
cl.exe /LDd /EHsc /W3 /Zi /std:c++latest /I"include" /I"C:\Users\zacha\AppData\Local\Programs\Python\Python314\include" /Fo"obj\debug\\" src\cpp\*.cpp /Fe:"bin\debug\Firelink_d.xll" /Fd:"bin\debug\Firelink_d.pdb" /link "lib\x64\XLCALL32.LIB" "C:\Users\zacha\AppData\Local\Programs\Python\Python314\libs\python3.lib"
