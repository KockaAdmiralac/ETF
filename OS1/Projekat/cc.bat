@echo off
set arg=%1
if "%arg%" == "" set arg=0
del src\user.cpp
rename test/user%arg%.cpp src/user.cpp
bcc +cc.txt c:\src\*.cpp applicat.lib > ccOutput
type ccOutput
del *.OBJ
rename src/user.cpp test/user%arg%.cpp
@echo on
