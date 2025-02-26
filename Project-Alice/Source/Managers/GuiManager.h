#pragma once

#include <pch.h>

namespace AliceUI
{
	// OpenGL
	void InitializeImGui_API_OpenGL(GLFWwindow* Context);
	void SetupFrame_API_OpenGL();
	void RenderImGui_API_OpenGL();
	void ShutdownImGui_API_OpenGL();

	// DirectX 11
	void InitializeImGui_API_DirectX11(HWND window, ID3D11Device* device, ID3D11DeviceContext* device_context);
	void SetupFrame_API_DirectX11();
	void RenderImGui_API_DirectX11();
	void ShutdownImGui_API_DirectX11();

	// Others

	void NewFrame();

	void SetStyle();

	bool CreateInstance(const char* title, bool* p_open = (bool*)0, ImGuiWindowFlags flags = 0);
	void EndInstance();

	void SimpleText(const char* text);

	template <typename type>
	inline void FormattedText(const char* format, type value)
	{
		ImGui::Text(format, value);
	}

	bool Checkbox(const char* title, bool* value);
	bool Button(const char* title);
	bool InputText(const char* title, std::string& buf);

	template <typename type>
	inline bool Input(const char* title, type* val)
	{
		if constexpr (std::is_same_v<type, float>)
		{
			return ImGui::InputFloat(title, val, 0.0f, 0.0f, "%.2f");
		}
		else if constexpr (std::is_same_v<type, int>)
		{
			return ImGui::InputInt(title, val);
		}
	}

	bool CreateNode(const char* title);
	void EndNode();

	template <typename type>
	inline bool CreateSlider(const char* title, type* value, type min_value, type max_value)
	{
		if constexpr (std::is_same_v<type, float>)
		{
			return ImGui::SliderFloat(title, value, min_value, max_value, "%.2f");
		}
		else if constexpr (std::is_same_v<type, int>)
		{
			return ImGui::SliderInt(title, value, min_value, max_value);
		}
	}

	bool IsFocused();
	void DoNotCaptureInputs();
	void CaptureInputs();
};