#pragma once
#include <pch.h>
#include <Overlay/API/OpenGL/Callbacks.h>
#include <thread>

namespace Alice
{
	namespace Overlay
	{
		// OpenGL 3.3 API Window
		class OpenGL
		{
		public:
			const char* Title;
			INT Width, Height;

		public:
			OpenGL(const char* title, int width, int height);
			~OpenGL();

			VOID Initialize();
			INT CreateContext();
			VOID ClearBuffers();
			VOID ClearColors();
			VOID SwapAndPoll();
			VOID Shutdown();

		public:
			bool IsRunning() { return !glfwWindowShouldClose(this->Context); }
			GLFWwindow* GetContext() { return this->Context; }
			float GetElapsedTime();

		private:
			GLFWwindow* Context;
			float elapsed_time = 0.0f;
		};

		// DirectX 11 API Window
		class DirectX11
		{
		public:
			LPCWSTR Title;
			LPCWSTR WindowClassName;
			INT	WIDTH, HEIGHT;

		public:
			DirectX11(LPCWSTR title, LPCWSTR windowclassname, INT width, INT height);
			~DirectX11();

			static LRESULT CALLBACK Window_Procedure(
					HWND window,
					UINT message,
					WPARAM w_param,
					LPARAM l_param
			);

			HWND InitializeWindow(
				HINSTANCE instance,
				int cmd_show
			);

			BOOL InitializeDirectX(
				HWND window, ID3D11Device** device,
				ID3D11DeviceContext** device_context,
				IDXGISwapChain** swap_chain,
				ID3D11RenderTargetView** render_target_view
			);

			VOID CleanUp(
				IDXGISwapChain* swap_chain,
				ID3D11Device* device,
				ID3D11DeviceContext* device_context,
				ID3D11RenderTargetView* render_target_view,
				HWND window,
				WNDCLASSEXW wc
			);

			VOID StartTimer();
			FLOAT GetElapsedTime();

		private:
			LARGE_INTEGER frequency;
			LARGE_INTEGER startTime;
		};

		void ShowErrorBox(const std::wstring& errorMessage, const std::wstring& errorTitle = L"Error");
		void ShowWarningBox(const std::wstring& warningMessage, const std::wstring& warningTitle = L"Warning");
		void ShowMessage(const std::wstring& message, const std::wstring& messageTitle = L"Message");
	}
}