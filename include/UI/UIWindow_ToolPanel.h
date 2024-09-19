#pragma once

#include <GUI_Helper.h>
#include <UI/UIWindow.h>

#include <simState.h>

class UIWindow_ToolPanel: public UIWindow {

private:
    // Variables
    std::vector<int> m_frequencyItems;
    int m_frequencyIndex;
    float m_duration;

    // Icons
    GUI_Helper::ImageData NewFileIcon;
    GUI_Helper::ImageData OpenFileIcon;
    GUI_Helper::ImageData SaveIcon;
    GUI_Helper::ImageData SaveAsIcon;
    GUI_Helper::ImageData UndoIcon;
    GUI_Helper::ImageData RedoIcon;
    GUI_Helper::ImageData CutIcon;
    GUI_Helper::ImageData CopyIcon;
    GUI_Helper::ImageData PasteIcon;
    GUI_Helper::ImageData TimerIcon;
    GUI_Helper::ImageData FrequencyIcon;
    GUI_Helper::ImageData SpeedIcon;
    GUI_Helper::ImageData CalculateIcon;
    GUI_Helper::ImageData StopIcon;
    GUI_Helper::ImageData Play_PauseIcon;

    // Private methods
    void loadIcons();
    void fileButtons();
    void editButtons();
    void frequency_durationInput();
    void playButtons();

public:
    // Variables
    simState m_state;
    
    // Event senders
    sigslot::signal0<> signal_NewFile;
    sigslot::signal1<std::string> signal_OpenFile;
    sigslot::signal0<> signal_Save;
    sigslot::signal1<std::string> signal_SaveAs;
    sigslot::signal0<> signal_Undo;
    sigslot::signal0<> signal_Redo;
    sigslot::signal0<> signal_Cut;
    sigslot::signal0<> signal_Copy;
    sigslot::signal0<> signal_Paste;
    sigslot::signal2<int, float> signal_Play;
    sigslot::signal0<> signal_Pause;
    sigslot::signal0<> signal_Stop;

    // Add class methods here
    UIWindow_ToolPanel(const char* p_title);
    void draw();
};