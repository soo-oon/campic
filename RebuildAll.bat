@echo off
if NOT DEFINED VS_CALL (
	call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VSDevCmd.bat"
	set VS_CALL=true
)
msbuild.exe %1 /p:configuration=debug /t:Clean;Rebuild /p:Platform="x86"
if not %errorlevel% == 0 goto End
msbuild.exe %1 /p:configuration=debug /t:Clean;Rebuild /p:Platform="x64“
if not %errorlevel% == 0 goto End
msbuild.exe %1 /p:configuration=release /t:Clean;Rebuild /p:Platform="x86"
if not %errorlevel% == 0 goto End
msbuild.exe %1 /p:configuration=release /t:Clean;Rebuild /p:Platform="x64"
:End 