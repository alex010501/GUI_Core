#pragma once

#include <MathAdditions.h>
#include <UI/UIWindow.h>
#include <UI/UIGraph.h>
#include <3D/BaseScene.h>
#include <random>
#include <math.h>


class UIWindow_3DWorkSpace: public UIWindow {
private:
    // Add variables here
    
    // Add methods here
public:
    // Add signals here

    // Add public variables here
    int windowWidth;
    int windowHeight;

    // Add public methods here
    UIWindow_3DWorkSpace(const char* p_title);

    void draw();
};