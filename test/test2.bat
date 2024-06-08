@echo off
set /p name="Enter your name: "
echo Hello, %name%!
set /p choice="Do you want to see the directory listing? (y/n): "

if "%choice%"=="y" (
    echo directory listing:
    dir
) else (
    echo exiting now.
)

