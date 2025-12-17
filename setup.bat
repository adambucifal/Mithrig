@echo off
echo Enter Maya version (e.g. 2025):
set /p MAYAVERSION=

call external\premake\premake5.exe vs2022 --mayaversion=%MAYAVERSION%

pause
