#include <iostream>
#include <string>
#include <vector>

#include <tinyfiledialogs.h>

#include <UI/UIWindow_ToolPanel.h>

UIWindow_ToolPanel::UIWindow_ToolPanel(const char* p_title): UIWindow(p_title)
{
    // Math variables
    this->m_state = SIM_STOP;
    this->m_duration = 10;
    this->m_frequencyItems = {25, 50, 100, 250, 500, 1000};
    this->m_frequencyIndex = 0;

    // Icons for the buttons
    this->loadIcons();
}

UIWindow_ToolPanel::~UIWindow_ToolPanel()
{
    this->freeIcons();
}

void UIWindow_ToolPanel::draw()
{
    
    // Set the window without the title bar
    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&window_class);

    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 50), ImVec2(FLT_MAX, 50));

    ImGui::Begin(m_title, nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // File, undo/redo, copy/paste buttons
    this->fileButtons();
    ImGui::SameLine(0, 25);
    this->editButtons();
    ImGui::SameLine(0, 25);

    // Frequency and duration input
    this->frequency_durationInput();
    ImGui::SameLine(0, 25);

    // Play/Pause/Stop buttons
    this->playButtons();

    // Add Neural Network stuff here
    
    
    ImGui::End();
}


void UIWindow_ToolPanel::loadIcons()
{
    bool lv_status = true;
    lv_status = UIHelper::loadImageFromFile("resources/Images/New.png", &this->NewFileIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Open.png", &this->OpenFileIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Save.png", &this->SaveIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/SaveAs.png", &this->SaveAsIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Undo.png", &this->UndoIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Redo.png", &this->RedoIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Cut.png", &this->CutIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Copy.png", &this->CopyIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Paste.png", &this->PasteIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Timer.png", &this->TimerIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Frequency.png", &this->FrequencyIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Speed.png", &this->SpeedIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Calculate.png", &this->CalculateIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Stop.png", &this->StopIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Play.png", &this->PlayIcon);
    IM_ASSERT(lv_status);
    lv_status = UIHelper::loadImageFromFile("resources/Images/Pause.png", &this->PauseIcon);
    IM_ASSERT(lv_status);
}

void UIWindow_ToolPanel::freeIcons()
{
    UIHelper::freeImage(this->NewFileIcon);
    UIHelper::freeImage(this->OpenFileIcon);
    UIHelper::freeImage(this->SaveIcon);
    UIHelper::freeImage(this->SaveAsIcon);
    UIHelper::freeImage(this->UndoIcon);
    UIHelper::freeImage(this->RedoIcon);
    UIHelper::freeImage(this->CutIcon);
    UIHelper::freeImage(this->CopyIcon);
    UIHelper::freeImage(this->PasteIcon);
    UIHelper::freeImage(this->TimerIcon);
    UIHelper::freeImage(this->FrequencyIcon);
    UIHelper::freeImage(this->SpeedIcon);
    UIHelper::freeImage(this->CalculateIcon);
    UIHelper::freeImage(this->StopIcon);
    UIHelper::freeImage(this->PlayIcon);
    UIHelper::freeImage(this->PauseIcon);
}

void UIWindow_ToolPanel::fileButtons()
{
    bool lv_buttonEnabled = (this->m_state == SIM_STOP);

    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->NewFileIcon), lv_buttonEnabled, "New"))
    {
        this->signal_NewFile();
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->OpenFileIcon), lv_buttonEnabled, "Open"))
    {
        const char* lv_extension[] = {"*.osg", "*.car"};
        const char* lv_filename = tinyfd_openFileDialog("Select a file", "", 2, lv_extension, "OSG and CAR Files", 0);
        
        if (lv_filename != NULL)
            this->signal_OpenFile(lv_filename);
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->SaveIcon), lv_buttonEnabled, "Save"))
    {
        this->signal_Save();
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->SaveAsIcon), lv_buttonEnabled, "SaveAs"))
    {        
        const char* lv_extension[] = {"*.osg", "*.car"};
        const char* lv_filename = tinyfd_saveFileDialog("Save as", "", 2, lv_extension, "OSG and CAR Files");
        
        if (lv_filename != NULL)
            this->signal_SaveAs(lv_filename);
    }
    
}

void UIWindow_ToolPanel::editButtons()
{    
    bool lv_buttonEnabled = (this->m_state == SIM_STOP);

    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->UndoIcon), lv_buttonEnabled, "Undo"))
    {
        this->signal_Undo();
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->RedoIcon), lv_buttonEnabled, "Redo"))
    {
        this->signal_Redo();
    }
    ImGui::SameLine(0, 25);

    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->CutIcon), lv_buttonEnabled, "Cut"))
    {
        this->signal_Cut();
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->CopyIcon), lv_buttonEnabled, "Copy"))
    {
        this->signal_Copy();
    }
    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(UIHelper::renderTexture(this->PasteIcon), lv_buttonEnabled, "Paste"))
    {
        this->signal_Paste();
    }
}

void UIWindow_ToolPanel::frequency_durationInput()
{
    bool lv_inputEnabled = (this->m_state == SIM_STOP);

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 2));
    UIHelper::ImGui_picture(UIHelper::renderTexture(this->FrequencyIcon));
    ImGui::SameLine();

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 5));
    ImGui::Text("Frequency");
    ImGui::SameLine();

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 5));  
    ImGui::PushItemWidth(80);
    ImGui::BeginDisabled(!lv_inputEnabled);
    if (ImGui::BeginCombo("Hz", std::to_string(this->m_frequencyItems[this->m_frequencyIndex]).c_str()))
    {
        for (int i = 0; i < this->m_frequencyItems.size(); ++i)
        {
            const bool isSelected = (this->m_frequencyIndex == i);
            if (ImGui::Selectable(std::to_string(this->m_frequencyItems[i]).c_str(), isSelected))
            {
                this->m_frequencyIndex = i;
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::EndDisabled();
    ImGui::PopItemWidth();
    ImGui::SameLine(0, 25);
    
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 2));
    UIHelper::ImGui_picture(UIHelper::renderTexture(this->TimerIcon));
    ImGui::SameLine();

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 5));
    ImGui::Text("Simulation time");
    ImGui::SameLine();

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 5));
    ImGui::PushItemWidth(80);
    ImGui::BeginDisabled(!lv_inputEnabled);
    ImGui::InputFloat("sec", &this->m_duration, 0.0f, 0.0f, "%.1f");
    // Check that the duration is between 0.1 and 120.
    if (this->m_duration < 0.1f)
    {
        this->m_duration = 0.1f;
    }
    else if (this->m_duration > 120.0f)
    {
        this->m_duration = 120.0f;
    }
    ImGui::EndDisabled();
    ImGui::PopItemWidth();
}

void UIWindow_ToolPanel::playButtons()
{
    UIHelper::TextureData lv_play_pause;
    switch (this->m_state)
    {
        case SIM_STOP: case SIM_PAUSE:
            lv_play_pause = UIHelper::renderTexture(this->PlayIcon);
            break;
        case SIM_PLAY:
            lv_play_pause = UIHelper::renderTexture(this->PauseIcon);
            break;
        default:
            break;
    }
    if (UIHelper::ImGui_imageButton(lv_play_pause, true, "Play/Pause"))
        switch (this->m_state)
        {
            case SIM_STOP: case SIM_PAUSE:
                this->m_state = SIM_PLAY;
                this->signal_Play(this->m_frequencyItems[this->m_frequencyIndex], this->m_duration);
                break;
            case SIM_PLAY:
                this->m_state = SIM_PAUSE;
                this->signal_Pause();
                break;
            default:
                break;
        }

    ImGui::SameLine();
    if (UIHelper::ImGui_imageButton(lv_play_pause = UIHelper::renderTexture(this->StopIcon), true, "Stop"))
    {
        this->m_state = SIM_STOP;
        this->signal_Stop();
    }
}