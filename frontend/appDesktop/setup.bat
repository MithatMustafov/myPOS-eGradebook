@echo off
setlocal

set HTTPLIB_DIR=src\lib
set HTTPLIB_PATH=%HTTPLIB_DIR%\httplib.h
set HTTPLIB_URL=https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

REM Create lib directory if it doesn't exist
if not exist "%HTTPLIB_DIR%" (
    echo Creating directory %HTTPLIB_DIR%
    mkdir "%HTTPLIB_DIR%"
)

REM Check if httplib.h exists
if exist "%HTTPLIB_PATH%" (
    echo httplib.h already exists in %HTTPLIB_DIR%
) else (
    echo Downloading httplib.h...
    powershell -Command "Invoke-WebRequest -Uri '%HTTPLIB_URL%' -OutFile '%HTTPLIB_PATH%'"
    if errorlevel 1 (
        echo ERROR: Failed to download httplib.h
        exit /b 1
    )
    echo Download completed.
)

pause
