@REM Install Dependencies using vcpkg

@ECHO OFF

if NOT EXIST vcpkg (
	git clone https://github.com/microsoft/vcpkg

	call .\vcpkg\bootstrap-vcpkg.bat

    call .\vcpkg\vcpkg.exe integrate install
)

call .\vcpkg\vcpkg.exe install osg  --clean-after-build

call .\vcpkg\vcpkg.exe install glfw3 bullet3 assimp tinyfiledialogs iniparser --clean-after-build