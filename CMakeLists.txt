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

# Bullet - physics library
find_package(Bullet CONFIG REQUIRED)

# GLFW, stb, tinyfiledialogs, iniparser
find_package(glfw3 CONFIG REQUIRED)
find_package(tinyfiledialogs CONFIG REQUIRED)
find_package(unofficial-iniparser CONFIG REQUIRED)

# OpenSceneGraph + OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(osg_OPENGL_PROFILE GL3)
find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgViewer osgDB osgGA osgUtil)
find_package(assimp CONFIG REQUIRED)

# ImGui
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/ImGuiInclude)

# EventHandler
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/EventHandler)

# STB_Image
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/stb_image)

# Set config file with variables 
set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(FONT_NAME "Cruinn_Bold.ttf")
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
target_link_libraries(GUI_Core PUBLIC ${BULLET_LIBRARIES})
target_include_directories(GUI_Core PUBLIC ${BULLET_INCLUDE_DIRS})

target_link_libraries(GUI_Core PUBLIC glfw)
target_link_libraries(GUI_Core PUBLIC stb_image)
target_link_libraries(GUI_Core PUBLIC tinyfiledialogs::tinyfiledialogs)
target_link_libraries(GUI_Core PUBLIC unofficial::iniparser::iniparser)

target_link_libraries(GUI_Core PUBLIC OpenGL::GL)
target_link_libraries(GUI_Core PUBLIC ${OPENSCENEGRAPH_LIBRARIES})
target_include_directories(GUI_Core PUBLIC ${OPENSCENEGRAPH_INCLUDE_DIRS})
target_link_libraries(GUI_Core PUBLIC assimp::assimp)

# Link ImGui
target_link_libraries(GUI_Core PUBLIC imguiInclude)
target_include_directories(GUI_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extern/ImGuiInclude)

# Link EventHandler
target_link_libraries(GUI_Core PUBLIC EventHandler)
target_include_directories(GUI_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extern/EventHandler/include)

# Example
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)

# Copy resources to bin
add_custom_command(TARGET GUI_Core POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources
                   ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/resources)