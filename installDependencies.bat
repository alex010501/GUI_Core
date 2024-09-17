@REM Install Dependencies using vcpkg

@ECHO OFF

if NOT EXIST vcpkg (
	git clone https://github.com/microsoft/vcpkg

	call .\vcpkg\bootstrap-vcpkg.bat

    call .\vcpkg\vcpkg.exe integrate install
)

call .\vcpkg\vcpkg.exe install glfw3 bullet3 vsg vsgxchange osg assimp opengl glew stb tinyfiledialogs iniparser --clean-after-build