#include <UIWindow_PropertiesViewer.h>

UIWindow_PropertiesViewer::UIWindow_PropertiesViewer(const char* p_title): UIWindow(p_title)
{

}

void UIWindow_PropertiesViewer::draw()
{
    ImGui::Begin(m_title);
    ImGui::Button("Properties Viewer");
    ImGui::End();
}