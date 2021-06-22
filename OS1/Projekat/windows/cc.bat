@echo off
set arg=%1
if "%arg%" == "" set arg=0
move test\user%arg%.cpp src\user.cpp
bcc +cc.txt src\*.cpp applicat.lib > ccOutput
type ccOutput
del *.OBJ
move src\user.cpp test\user%arg%.cpp
@echo on
