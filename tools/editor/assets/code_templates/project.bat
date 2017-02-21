:: Install Visual studio build environment
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

IF /I "%ERRORLEVEL%" NEQ "0" (
    call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
)

:: Switch to Build Directory
pushd %~dp0

::Perform Action
if "%1%"=="configure" (
	cd src
	if not exist build\NUL mkdir build
	cd build
    cmake ..
)
if "%1%"=="build" (
	cd src\build
	devenv.exe Test01.sln /build Debug
)

popd