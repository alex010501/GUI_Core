#include <UI/UIHelper.h>

bool UIHelper::loadImageFromFile(const char* p_filename, UIHelper::ImageData* p_out_imageMemory)
{
    int lv_image_width = 0;
    int lv_image_height = 0;
    unsigned char* lv_image_data = stbi_load(p_filename, &lv_image_width, &lv_image_height, NULL, 4);
    if (lv_image_data == NULL)
        return false;
    p_out_imageMemory->image_data = lv_image_data;
    p_out_imageMemory->width = lv_image_width;
    p_out_imageMemory->height = lv_image_height;
    return true;
}
UIHelper::TextureData UIHelper::renderTexture(UIHelper::ImageData p_imageData)
{
    GLuint lv_image_texture;
    glGenTextures(1, &lv_image_texture);
    glBindTexture(GL_TEXTURE_2D, lv_image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
    
    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_imageData.width, p_imageData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_imageData.image_data);
    
    UIHelper::TextureData lv_textureData;

    lv_textureData.texture = (void*)(intptr_t)lv_image_texture;
    lv_textureData.width = p_imageData.width;
    lv_textureData.height = p_imageData.height;
    return lv_textureData;
}
void UIHelper::freeImage(UIHelper::ImageData imageData)
{
    stbi_image_free(imageData.image_data);
}

/*bool UIHelper::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
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
}*/

bool UIHelper::ImGui_imageButton(UIHelper::TextureData p_imageData, bool p_enabled, std::string p_buttonName)
{   
    ImGui::BeginDisabled(!p_enabled);
    bool ret = ImGui::IsItemClicked(ImGui::ImageButton(p_buttonName.c_str(), p_imageData.texture, ImVec2(p_imageData.width, p_imageData.height)));
    ImGui::EndDisabled();
    return ret;
}

void UIHelper::ImGui_picture(UIHelper::TextureData p_imageData)
{
    ImGui::Image(p_imageData.texture, ImVec2(p_imageData.width, p_imageData.height));
}