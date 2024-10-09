#include <UI/UIHelper.h>

bool UIHelper::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
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

UIHelper::ImageData UIHelper::LoadImg(const char* filename)
{
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    bool ret = UIHelper::LoadTextureFromFile(filename, &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    UIHelper::ImageData imageData;
    imageData.texture = (void*)(intptr_t)my_image_texture;
    imageData.width = my_image_width;
    imageData.height = my_image_height;

    return imageData;
}

bool UIHelper::ImGui_imageButton(UIHelper::ImageData imageData, bool enabled, std::string buttonName)
{   
    ImGui::BeginDisabled(!enabled);
    bool ret = ImGui::IsItemClicked(ImGui::ImageButton(buttonName.c_str(), imageData.texture, ImVec2(imageData.width, imageData.height)));
    ImGui::EndDisabled();
    return ret;
}

void UIHelper::ImGui_picture(UIHelper::ImageData imageData)
{
    ImGui::Image(imageData.texture, ImVec2(imageData.width, imageData.height));
}

std::string UIHelper::labelPrefix(const char* p_label)
{
    // ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
	ImGui::Text(p_label); 
	ImGui::SameLine();
    // ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2);

	std::string labelID = "##";
	labelID += p_label;

	return labelID;
}

/*bool UIHelper::BeginButtonDropDown(const char *label, ImVec2 buttonSize)
{
    ImGui::SameLine(0.f, 0.f);

    ImGui::ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiState &g = *GImGui;
    const ImGuiStyle &style = g.Style;

    float x = ImGui::GetCursorPosX();
    float y = ImGui::GetCursorPosY();

    ImVec2 size(20, buttonSize.y);
    bool pressed = ImGui::Button("##", size);

    // Arrow
    ImVec2 center(window->Pos.x + x + 10, window->Pos.y + y + buttonSize.y / 2);
    float r = 8.f;
    center.y -= r * 0.25f;
    ImVec2 a = center + ImVec2(0, 1) * r;
    ImVec2 b = center + ImVec2(-0.866f, -0.5f) * r;
    ImVec2 c = center + ImVec2(0.866f, -0.5f) * r;

    window->DrawList->AddTriangleFilled(a, b, c, GetColorU32(ImGuiCol_Text));

    // Popup

    ImVec2 popupPos;

    popupPos.x = window->Pos.x + x - buttonSize.x;
    popupPos.y = window->Pos.y + y + buttonSize.y;

    ImGui::SetNextWindowPos(popupPos);

    if (pressed)
    {
        ImGui::OpenPopup(label);
    }

    if (ImGui::BeginPopup(label))
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_Button]);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, style.Colors[ImGuiCol_Button]);
        ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, style.Colors[ImGuiCol_Button]);
        return true;
    }

    return false;
}

void UIHelper::EndButtonDropDown()
{
    ImGui::PopStyleColor(3);
    ImGui::EndPopup();
}*/