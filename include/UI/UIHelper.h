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
        unsigned char* image_data;
        int width;
        int height;
    };

    struct TextureData
    {
        ImTextureID texture;
        int width;
        int height;
    };

    bool loadImageFromFile(const char* p_filename, ImageData* p_out_imageMemory);

    TextureData renderTexture(ImageData p_imageData);
    
    void freeImage(ImageData p_imageData);
    
    // bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

    // ImageData LoadImg(const char* filename);

    bool ImGui_imageButton(TextureData p_imageData, bool p_enabled, std::string p_buttonName);

    void ImGui_picture(TextureData p_imageData);
};