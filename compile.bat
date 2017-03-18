@echo off

if "%1" == "all" (
	call:compileAll %2
) else if "%1" == "" (
	call:compileAll %2
) else (
	call:compile %1 %2 %3
)
goto:eof

:compileAll
	call:compile "sprites" %1 "batch"

goto:eof

:compile
	if exist "resources\%~1\\" (
		if not exist "resources\obj\%~1\\" mkdir "resources\obj\%~1\\"
	
		x64\Release\archiveWriter.exe "resources\%~1\\" "resources\obj\%~1\\" "resources\%~1.dat" "%~2" "%~3"
	) else (
		@echo on
		@echo "%~1 not found"
		@echo off
	)
	
goto:eof