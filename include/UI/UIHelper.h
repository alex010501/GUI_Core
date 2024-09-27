#pragma once

#include <string>

// GUI include
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stb_image.h>

// OSG include
#include <osgViewer/Viewer>
#include <osgViewer/config/SingleWindow>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

namespace UIHelper
{
    struct ImageData
    {
        ImTextureID texture;
        int width;
        int height;
    };
    
    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

    ImageData LoadImg(const char* filename);

    bool ImGui_imageButton(ImageData imageData, bool enabled, std::string buttonName);

    void ImGui_picture(ImageData imageData);
};