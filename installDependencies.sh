# Install Dependencies using vcpkg

if [ ! -d "vcpkg" ]; then
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ./vcpkg integrate install
    cd ..
fi

./vcpkg/vcpkg install osg glfw3 bullet3 assimp tinyfiledialogs iniparser --clean-after-build