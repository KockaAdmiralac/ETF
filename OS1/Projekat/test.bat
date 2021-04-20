@echo off
bcc +cc.txt -DKERNEL_DEBUG=1 c:\src\*.cpp %1 applicat.lib > ccOutput
type ccOutput
del *.OBJ
@echo on
