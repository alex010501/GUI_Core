@REM Install Dependencies using vcpkg

@ECHO OFF

if NOT EXIST vcpkg (
	git clone https://github.com/microsoft/vcpkg

	call .\vcpkg\bootstrap-vcpkg.bat

    call .\vcpkg\vcpkg.exe integrate install
)

call .\vcpkg\vcpkg.exe install osg glfw3 bullet3 assimp stb tinyfiledialogs iniparser --clean-after-build