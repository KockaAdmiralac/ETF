@echo off
bcc +cc.txt c:\src\*.cpp %1 applicat.lib > ccOutput
type ccOutput
del *.obj
@echo on
