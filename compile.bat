@echo off

if "%1" == "all" (
	call:compile "sprites"
) else if "%1" == "" (
	call:compile "sprites"
) else (
	call:compile %1
)
goto:eof

:compile
	archiveWriter.exe "resources\%~1\\" "resources\obj\%~1\\" "resources\%~1.dat" "batch"
	
goto:eof