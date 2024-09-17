#pragma once

#define GLFW_INCLUDE_NONE

#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#elif defined(__APPLE__)
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <UI/UIWindow.h>
#include <3D/BaseScene.h>
#include <sigslot.h>
#include <timer.h>

#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <osgViewer/Viewer>
#include <osgViewer/config/SingleWindow>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

class CustomTrackballManipulator : public osgGA::TrackballManipulator
{
public:
    void pan(double dx, double dy, double scale)
    {
        panModel(-dx * scale, dy * scale);
    }

    void rotate(float dx, float dy, double scale)
    {
        rotateTrackball(0.0, 0.0, -dx, dy, scale);
    }
};

class CoreWindow: public sigslot::has_slots<>
{
private:
    osgViewer::Viewer m_viewer;
    osg::ref_ptr<CustomTrackballManipulator> m_manipulator;
    Timer m_fpsTimer;
    GLFWwindow* m_window;
    GLFWimage* m_icon;
    int m_width;
    int m_height;
    const char* m_title;
    const char* m_iconPath;
    bool rightMousePressed = false;
    bool leftMousePressed = false;
    bool middleMousePressed = false;
    bool shiftPressed = false;
    double lastX = 0;
    double lastY = 0;
protected:
    std::vector<UIWindow*> m_GUIWindows;
    BaseScene m_scene;
    osg::Vec4 m_clearColor = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

    bool isOpen()
    {
        return !glfwWindowShouldClose(m_window);
    }

    void draw();

    virtual void drawGUI(){};

    virtual void initGuiDockspace(){};

    virtual void initSignals(){};

    virtual void update(){};

    virtual void loadScene(const char* scenePath){};

    void setCallbacks();

    void resizeCallback(int p_width, int p_height);

    void posCallback(int p_xpos, int p_ypos);

    void keyCallback(int p_key, int p_scancode, int p_action, int p_mods);

    void scrollCallback(double p_xoffset, double p_yoffset);

    void mouseButtonCallback(int p_button, int p_action, int p_mods);

    void cursorPosCallback(double p_xpos, double p_ypos);
public:
    CoreWindow(const char* p_title, const char* p_iconPath = nullptr, int p_width = 1280, int p_height = 720);

    int run(const char* scenePath = nullptr);
};


namespace GUI_Helper
{
    struct ImageData
    {
        ImTextureID texture;
        int width;
        int height;
    };
    
    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

    ImageData LoadImg(const char* filename);

    bool ImGui_imageButton(ImageData imageData, bool enabled);

    void ImGui_picture(ImageData imageData);
};