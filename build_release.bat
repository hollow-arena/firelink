@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
if %errorlevel% neq 0 exit /b %errorlevel%
if not exist obj\release mkdir obj\release
if not exist bin\release mkdir bin\release
cl.exe /LD /EHsc /W3 /O2 /std:c++latest /I"include" /I"C:\Users\zacha\AppData\Local\Programs\Python\Python314\include" /Fo"obj\release\\" src\cpp\*.cpp /Fe:"bin\release\Firelink.xll" /link "lib\x64\XLCALL32.LIB" "C:\Users\zacha\AppData\Local\Programs\Python\Python314\libs\python3.lib"