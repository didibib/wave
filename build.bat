@ECHO OFF
IF NOT EXIST "build\" MKDIR "build\"
CD build
cmake .. -G "Visual Studio 17 2022" -A x64
PAUSE