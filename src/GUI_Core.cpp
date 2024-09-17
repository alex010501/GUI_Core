#include <GUI_Core.h>

CoreWindow::CoreWindow(const char *p_title,
                       const char* p_iconPath,
                       int p_width, int p_height):
                       m_title(p_title), m_iconPath(p_iconPath), m_width(p_width), m_height(p_height)
{
    
}

int CoreWindow::run(const char* scenePath)
{
    // Connect app with GUI windows
    this->initSignals();

    // Initialise GLFW
    if (!glfwInit())
    {
        // Handle initialization error
        return 1;
    }
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);   
    // Create GLFW window
    this->m_window = glfwCreateWindow(this->m_width, this->m_height, this->m_title, NULL, NULL);
    if (!this->m_window)
    {
        glfwTerminate();
        return 2;
    }    
    glfwSetWindowSizeLimits(this->m_window, 640, 360, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // Set Icon
    if (this->m_iconPath)
    {
        int lv_image_width, lv_image_height, lv_image_channels;
        unsigned char* lv_image_data = stbi_load(this->m_iconPath, &lv_image_width, &lv_image_height, &lv_image_channels, 0);
        if (lv_image_data)
        {
            this->m_icon = new GLFWimage;
            this->m_icon[0].width = lv_image_width;
            this->m_icon[0].height = lv_image_height;
            this->m_icon[0].pixels = lv_image_data;
            glfwSetWindowIcon(this->m_window, 1, this->m_icon);
        }
        else
        {
            std::cout << "Failed to load image: " << this->m_iconPath << std::endl;
            stbi_image_free(lv_image_data);
            this->m_icon = NULL;
            glfwSetWindowIcon(this->m_window, 0, NULL);
        }
    }
    else
    {
        this->m_icon = NULL;
        glfwSetWindowIcon(this->m_window, 0, NULL);
    }
    glfwMakeContextCurrent(this->m_window);
    glfwSwapInterval(1); // Enable vsync
    this->setCallbacks();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    for (auto lv_GUI_windows: this->m_GUIWindows)
        lv_GUI_windows->setupFileDialog();

    // Initialize OSG viewer
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->readDISPLAY();
    traits->setUndefinedScreenDetailsToDefaultScreen();
    traits->windowName = this->m_title;    
    this->m_viewer.setUpViewerAsEmbeddedInWindow(0, 0, this->m_width, this->m_height);   
    this->m_viewer.getCamera()->setGraphicsContext(new osgViewer::GraphicsWindowEmbedded(traits.get()));
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    this->m_viewer.getCamera()->setViewport(new osg::Viewport(0, 0, mode->width, mode->height));

    // Maximize window
    glfwMaximizeWindow(this->m_window);

    // load scene in 3D workspace
    this->loadScene(scenePath);

    // set up viewer
    this->m_viewer.getCamera()->setClearColor(this->m_clearColor);
    this->m_viewer.setSceneData(this->m_scene.getSceneRoot());
    
    osg::Vec3 eye(2.0, 2.0, 2.0);
    osg::Vec3 center(0.0, 0.0, 0.0);
    osg::Vec3 up(0.0, 1.0, 0.0);
    this->m_viewer.getCamera()->setViewMatrixAsLookAt(eye, center, up);

    this->m_manipulator = new CustomTrackballManipulator;
    this->m_viewer.setCameraManipulator(this->m_manipulator);    

    auto updateMethod = std::bind(&CoreWindow::update, this);
    std::thread updateThread(updateMethod);
    this->m_fpsTimer.setFrequency(60);
    this->m_fpsTimer.start();

    while (!glfwWindowShouldClose(this->m_window))
    {        
        this->draw();
        glfwSwapBuffers(this->m_window);
        glfwPollEvents();
        this->m_fpsTimer.wait();
    }

    updateThread.join();

    // ImGui shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();

    // GLFW shutdown
    stbi_image_free(this->m_icon[0].pixels);
    glfwDestroyWindow(this->m_window);
    glfwTerminate();

    return 0;
}

void CoreWindow::draw()
{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Dockspace settings
    this->initGuiDockspace();

    // Render subwindows
    this->drawGUI();

    // Prepare ImGui data for rendering
    ImGui::Render();
    ImGui::UpdatePlatformWindows();

    // OSG render
    this->m_viewer.frame();

    // ImGui-OpenGL render
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CoreWindow::resizeCallback(int p_width, int p_height)
{
    this->m_width = p_width;
    this->m_height = p_height;
    this->draw();
}

void CoreWindow::posCallback(int p_x, int p_y)
{
    glfwSetWindowPos(this->m_window, p_x, p_y);
    this->draw();
}

void CoreWindow::keyCallback(int p_key, int p_scancode, int p_action, int p_mods)
{
    if     (p_key == GLFW_KEY_LEFT_SHIFT && p_action == GLFW_PRESS)
    {
        this->shiftPressed = true;
    }
    else if (p_key == GLFW_KEY_LEFT_SHIFT && p_action == GLFW_RELEASE)
    {
        this->shiftPressed = false;
    }
}

void CoreWindow::scrollCallback(double p_xoffset, double p_yoffset)
{
    int k;
    if (this->shiftPressed)
    {
        k = 10;
    }
    else
    {
        k = 1;
    }
    this->m_manipulator->setDistance(this->m_manipulator->getDistance() - k * p_yoffset);
}

void CoreWindow::mouseButtonCallback(int p_button, int p_action, int p_mods)
{
    if      (p_button == GLFW_MOUSE_BUTTON_RIGHT  && p_action == GLFW_PRESS)
    {
        this->rightMousePressed = true;
    }
    else if (p_button == GLFW_MOUSE_BUTTON_RIGHT  && p_action == GLFW_RELEASE)
    {
        this->rightMousePressed = false;
    }
    else if (p_button == GLFW_MOUSE_BUTTON_MIDDLE && p_action == GLFW_PRESS)
    {
        this->middleMousePressed = true;
    }
    else if (p_button == GLFW_MOUSE_BUTTON_MIDDLE && p_action == GLFW_RELEASE)
    {
        this->middleMousePressed = false;
    }
}

void CoreWindow::cursorPosCallback(double p_x, double p_y)
{
    double dx = p_x - this->lastX;
    double dy = p_y - this->lastY;
    double k1 = 0.0001;
    double k2 = 0.0005;
    double l = this->m_manipulator->getDistance();
    if (this->rightMousePressed)
    {
        this->m_manipulator->rotate(dx, dy, l * k1);
    }
    if (this->middleMousePressed)
    {
        this->m_manipulator->pan(dx, dy, l * k2);
    }
    this->lastX = p_x;
    this->lastY = p_y;
}

void CoreWindow::setCallbacks()
{
    // Set GLFW window user pointer
    glfwSetWindowUserPointer(this->m_window, this);
    
    // Set GLFW callbacks
    auto CoreWindowResizeCallback = [](GLFWwindow* p_window, int p_width, int p_height)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->resizeCallback(p_width, p_height);
    };
    glfwSetWindowSizeCallback(this->m_window, CoreWindowResizeCallback);

    auto CoreWindowPosCallback = [](GLFWwindow* p_window, int p_x, int p_y)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->posCallback(p_x, p_y);
    };
    glfwSetWindowPosCallback(this->m_window, CoreWindowPosCallback);

    auto CoreWindowScrollCallback = [](GLFWwindow* p_window, double p_xoffset, double p_yoffset)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->scrollCallback(p_xoffset, p_yoffset);
    };
    glfwSetScrollCallback(this->m_window, CoreWindowScrollCallback);

    auto CoreWindowMouseButtonCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->mouseButtonCallback(p_button, p_action, p_mods);
    };
    glfwSetMouseButtonCallback(this->m_window, CoreWindowMouseButtonCallback);

    auto CoreWindowCursorPosCallback = [](GLFWwindow* p_window, double p_xpos, double p_ypos)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->cursorPosCallback(p_xpos, p_ypos);
    };
    glfwSetCursorPosCallback(this->m_window, CoreWindowCursorPosCallback);

    auto CoreWindowKeyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
    {
        static_cast<CoreWindow*>(glfwGetWindowUserPointer(p_window))->keyCallback(p_key, p_scancode, p_action, p_mods);
    };
    glfwSetKeyCallback(this->m_window, CoreWindowKeyCallback);
}


// Addition helper functions
bool GUI_Helper::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);

    if (image_data == NULL)
        return false;
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
    
    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

GUI_Helper::ImageData GUI_Helper::LoadImg(const char* filename)
{
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    bool ret = GUI_Helper::LoadTextureFromFile(filename, &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    GUI_Helper::ImageData imageData;
    imageData.texture = (void*)(intptr_t)my_image_texture;
    imageData.width = my_image_width;
    imageData.height = my_image_height;

    return imageData;
}

bool GUI_Helper::ImGui_imageButton(GUI_Helper::ImageData imageData, bool enabled)
{   
    ImGui::BeginDisabled(!enabled);
    bool ret = ImGui::IsItemClicked(ImGui::ImageButton("Button", imageData.texture, ImVec2(imageData.width, imageData.height)));
    ImGui::EndDisabled();
    return ret;
}

void GUI_Helper::ImGui_picture(GUI_Helper::ImageData imageData)
{
    ImGui::Image(imageData.texture, ImVec2(imageData.width, imageData.height));
}