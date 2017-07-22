call ../env
@echo off
set BUILD_DIR=build
if "%1%" == "clean" (
    goto clean
)
if "%1%" == "all-clean" (
    goto aclean
)

goto build

:build
if not exist %BUILD_DIR% (
    md %BUILD_DIR%
)
cd build
set GEN="MinGW Makefiles"
cmake -G %GEN% .. -DCMAKE_BUILD_TYPE=Debug
mingw32-make
exit

:aclean
if exist %BUILD_DIR% (
    rd /s /q %BUILD_DIR%
)
exit

:clean
if exist %BUILD_DIR% (
    cd %BUILD_DIR%
    mingw32-make clean
)
exit