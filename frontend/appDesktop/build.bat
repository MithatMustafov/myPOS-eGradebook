@echo off
REM === Change this path to your Visual Studio vcvarsall.bat location ===
set VS_VCVARS="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

if not exist %VS_VCVARS% (
    echo ERROR: Visual Studio environment setup script not found at %VS_VCVARS%
    pause
    exit /b 1
)

REM Call vcvarsall.bat for 64-bit environment
call %VS_VCVARS% x64

REM Create build folder if it doesn't exist
if not exist build (
    mkdir build
)

REM Compile all source files
cl /EHsc /I src ^
    src\main.cpp ^
    src\asciiArt\asciiMyPOS.cpp ^
    src\menu\Menu.cpp ^
    src\menu\MenuFunctions.cpp ^
    src\menu\actions\StudentActions.cpp ^
    src\menu\actions\SubjectActions.cpp ^
    src\menu\actions\GradeActions.cpp ^
    src\menu\actions\AnalyticsActions.cpp ^
    /Fe:build\main.exe

REM Pause so you can see compiler output
pause
