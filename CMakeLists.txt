# CMake version
cmake_minimum_required(VERSION 3.30)

# Check subproject or not
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "Building GUI_Core as main project")
    # Set vcpkg toolchain
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

# Project name
project(GUI_Core)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})

# External libraries
find_package(glfw3 CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

find_package(stb REQUIRED)
find_package(tinyfiledialogs CONFIG REQUIRED)
find_package(unofficial-iniparser CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

find_package(Vulkan REQUIRED)
find_package(vsg CONFIG REQUIRED)
find_package(vsgXchange CONFIG REQUIRED)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
set(osg_OPENGL_PROFILE GL3)
find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgViewer osgDB osgGA osgUtil) 

# ImGui
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/ImGuiInclude)

# EventHandler
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/EventHandler)

# Set config file with variables 
set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/res")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMake/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h @ONLY)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the source files for your project
# Set 'GUI_Source' variable 
file(GLOB_RECURSE GUI_Sources CONFIGURE_DEPENDS "include/*.h"
                                                "src/*.cpp")
                                                
# Build GUI_Core library
add_library(GUI_Core STATIC ${GUI_Sources})

# Link and include external libraries
target_link_libraries(GUI_Core PRIVATE glfw)
target_link_libraries(GUI_Core PRIVATE ${BULLET_LIBRARIES})
target_link_libraries(GUI_Core PRIVATE vsg::vsg)
target_link_libraries(GUI_Core PRIVATE vsgXchange::vsgXchange)
target_link_libraries(GUI_Core PRIVATE tinyfiledialogs::tinyfiledialogs)
target_link_libraries(GUI_Core PRIVATE OpenGL::GL)
target_link_libraries(GUI_Core PRIVATE GLEW::GLEW)
target_include_directories(GUI_Core PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(GUI_Core PRIVATE unofficial::iniparser::iniparser)

target_link_libraries(GUI_Core PRIVATE assimp::assimp)

target_link_libraries(GUI_Core PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_include_directories(GUI_Core PUBLIC ${OPENSCENEGRAPH_INCLUDE_DIRS})

target_link_libraries(GUI_Core PUBLIC EventHandler)
target_include_directories(GUI_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extern/EventHandler/include)

# Link ImGui
target_link_libraries(GUI_Core PUBLIC imguiInclude)
target_include_directories(GUI_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extern/ImGuiInclude)

# Example
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)