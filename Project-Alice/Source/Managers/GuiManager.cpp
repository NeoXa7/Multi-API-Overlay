#include "GuiManager.h"

namespace AliceUI
{
    // OpenGL
    void InitializeImGui_API_OpenGL(GLFWwindow* Context)
    {
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(Context, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        io.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto.ttf", 15.0f);
        io.Fonts->Build();     
    }

    void SetupFrame_API_OpenGL()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void RenderImGui_API_OpenGL()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ShutdownImGui_API_OpenGL()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

	// DirectX 11
    void InitializeImGui_API_DirectX11(HWND window, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(device, device_context);
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto.ttf", 15.0f);
        io.Fonts->Build();
    }

    void SetupFrame_API_DirectX11()
    {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
    }

    void RenderImGui_API_DirectX11()
	{
        ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    void ShutdownImGui_API_DirectX11()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    // Others

    void NewFrame()
    {
        ImGui::NewFrame();
    }

    void SetStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowBorderSize = 1.0f;
        style.WindowRounding = 1.0f;
        style.ScrollbarSize = 2.0f;
        style.Colors[ImGuiCol_TitleBg] = ImColor(14, 14, 14);
        style.Colors[ImGuiCol_TitleBgActive] = ImColor(14, 14, 14);
        style.Colors[ImGuiCol_FrameBg] = ImColor(31, 57, 88);
        style.Colors[ImGuiCol_FrameBgHovered] = ImColor(41, 67, 98);
        style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0);
    }

    bool CreateInstance(const char* title, bool* p_open, ImGuiWindowFlags flags)
    {
        return ImGui::Begin(title, p_open, flags | ImGuiWindowFlags_NoFocusOnAppearing);
    }

    void EndInstance()
    {
        ImGui::End();
    }

    void SimpleText(const char* text)
    {
        ImGui::Text(text);
    }

    bool Checkbox(const char* title, bool* value)
    {
        return ImGui::Checkbox(title, value);
    }

    bool Button(const char* title)
    {
        return ImGui::Button(title);
    }

    bool InputText(const char* title, std::string& buf)
    {
        // Create a buffer large enough to hold user input
        char inputBuffer[256];

        // Copy the current string content into the buffer
        strncpy_s(inputBuffer, buf.c_str(), sizeof(inputBuffer));
        inputBuffer[sizeof(inputBuffer) - 1] = '\0';  // Ensure null termination

        // Render the input text field
        bool modified = ImGui::InputText(title, inputBuffer, sizeof(inputBuffer));

        // If modified, update the string
        if (modified)
        {
            buf = inputBuffer;
        }

        return modified;
    }

    bool CreateNode(const char* title)
    {
        return ImGui::TreeNode(title);
    }

    void EndNode()
    {
        ImGui::TreePop();
    }

    bool IsFocused()
    {
        if (!ImGui::IsAnyItemActive() && /*!ImGui::IsAnyItemHovered() &&*/ !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void DoNotCaptureInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.WantCaptureMouse = false;
        io.WantCaptureKeyboard = false;
    }

    void CaptureInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.WantCaptureMouse = true;
        io.WantCaptureKeyboard = true;
    }

}

