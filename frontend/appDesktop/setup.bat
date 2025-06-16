@echo off
setlocal

set HTTPLIB_DIR=src\lib
set HTTPLIB_PATH=%HTTPLIB_DIR%\httplib.h
set HTTPLIB_URL=https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

set JSON_DIR=src\lib\nlohmann
set JSON_PATH=%JSON_DIR%\json.hpp
set JSON_URL=https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

REM Create lib directory if it doesn't exist
if not exist "%HTTPLIB_DIR%" (
    echo Creating directory %HTTPLIB_DIR%
    mkdir "%HTTPLIB_DIR%"
)

REM Create nlohmann directory if it doesn't exist
if not exist "%JSON_DIR%" (
    echo Creating directory %JSON_DIR%
    mkdir "%JSON_DIR%"
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

REM Check if json.hpp exists
if exist "%JSON_PATH%" (
    echo json.hpp already exists in %JSON_DIR%
) else (
    echo Downloading json.hpp...
    powershell -Command "Invoke-WebRequest -Uri '%JSON_URL%' -OutFile '%JSON_PATH%'"
    if errorlevel 1 (
        echo ERROR: Failed to download json.hpp
        exit /b 1
    )
    echo Download completed.
)

pause
