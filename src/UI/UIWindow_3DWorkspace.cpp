#include <UIWindow_3DWorkspace.h>

UIWindow_3DWorkSpace::UIWindow_3DWorkSpace(const char* p_title):
                      UIWindow(p_title)
{
    this->windowWidth = 0;
    this->windowHeight = 0;
}

void UIWindow_3DWorkSpace::draw()
{
    // ImVec4 overlayColour = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);

    // ImGui::PushStyleColor(ImGuiCol_WindowBg, overlayColour); // 1 (outside begin)
    // ImGui::SetNextWindowBgAlpha(0.0f); // 2    

    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&window_class);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin(this->m_title);//, nullptr, ImGuiWindowFlags_NoBackground);// | ImGuiWindowFlags_NoInputs);

    // ImGui::PushStyleColor(ImGuiCol_WindowBg, overlayColour); // 3 (inside begin)
    //     ImGui::PopStyleColor();

    ImGui::Button("3D Workspace");
    // we access the ImGui window size
    this->windowWidth  = ImGui::GetContentRegionAvail().x;
    this->windowHeight = ImGui::GetContentRegionAvail().y;
    
    ImGui::End();
    // ImGui::PopStyleColor();
}