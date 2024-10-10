@REM Install Dependencies using vcpkg

@ECHO OFF

if NOT EXIST vcpkg (
	git clone https://github.com/microsoft/vcpkg

	call .\vcpkg\bootstrap-vcpkg.bat

    call .\vcpkg\vcpkg.exe integrate install
)

call .\vcpkg\vcpkg.exe install osg:x64-windows-static glfw3:x64-windows-static bullet3:x64-windows-static assimp:x64-windows-static tinyfiledialogs:x64-windows-static iniparser:x64-windows-static --clean-after-build