@echo off
set arg=%1
if "%arg%" == "" set arg=0
del src\user.cpp
move test\user%arg%.cpp src\user.cpp
bcc +cc.txt -DKERNEL_DEBUG=1 src\*.cpp applicat.lib > ccOutput
type ccOutput
del *.OBJ
move src\user.cpp test\user%arg%.cpp
@echo on
