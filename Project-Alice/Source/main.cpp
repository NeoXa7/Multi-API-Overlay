#include <pch.h>
#include <Overlay/Overlay.h>
#include <Globals/API.h>
#include <Globals/Globals.h>
#include <Managers/DataManager.h>
#include <Managers/GuiManager.h>

Alice::Overlay::OpenGL opengl_api_window("Project Alice", 800, 600);
Alice::Overlay::DirectX11 dx11_api_window(L"Project Alice", L"PROJECT_ALICE_CLASS_001", SCREEN_WIDTH, SCREEN_HEIGHT);

void RenderInterface()
{
	AliceUI::SetStyle();

	AliceUI::CreateInstance("Project Alice", nullptr);
	{
		if (AliceUI::Button("Set API to DirectX11"))
		{
			Alice::Overlay::ShowMessage(L"Please restart the application to apply the changes.");
			DataManager::save_renderer_api_config(DIRECTX11_API);
		}

		if (AliceUI::Button("Set API to OpenGL3"))
		{
			Alice::Overlay::ShowMessage(L"Please restart the application to apply the changes.");
			DataManager::save_renderer_api_config(OPENGL_API);
		}

		if (DataManager::get_api() == std::to_string(DIRECTX11_API))
		{
			AliceUI::FormattedText<std::string>("Current API : %s", "DirectX11");
			AliceUI::FormattedText<float>("Elapsed Time : %.1f", dx11_api_window.GetElapsedTime());
		}
		else if (DataManager::get_api() == std::to_string(OPENGL_API))
		{
			AliceUI::FormattedText<std::string>("Current API : %s", "OpenGL 3.3");
			AliceUI::FormattedText<float>("Elapsed Time : %.1f", opengl_api_window.GetElapsedTime());
		}

		AliceUI::SimpleText("Visibility Key: INSERT");
	}

	AliceUI::EndInstance();
}

auto WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show) -> INT
{
    if (DataManager::get_api() == std::to_string(DIRECTX11_API))
    {
		Alice::API::CurrentRendererAPI = Alice::API::RendererAPI::DirectX;
	}
    else if (DataManager::get_api() == std::to_string(OPENGL_API))
    {
        Alice::API::CurrentRendererAPI = Alice::API::RendererAPI::OpenGL;
    }

	// OpenGL API Window
	if (Alice::API::CurrentRendererAPI == Alice::API::RendererAPI::OpenGL)
	{
		opengl_api_window.Initialize();
		opengl_api_window.CreateContext();
		AliceUI::InitializeImGui_API_OpenGL(opengl_api_window.GetContext());


		while (opengl_api_window.IsRunning())
		{
			AliceUI::SetupFrame_API_OpenGL();
			AliceUI::NewFrame();

			if (GetAsyncKeyState(VK_INSERT) & 1)
			{
				Globals::m_bIsVisible = !Globals::m_bIsVisible;
			}

			if (Globals::m_bIsVisible)
			{
				glfwSetWindowAttrib(opengl_api_window.GetContext(), GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);
			}
			else
			{
				glfwSetWindowAttrib(opengl_api_window.GetContext(), GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
			}

			if (Globals::m_bIsVisible)
			{
				RenderInterface();
			}

			opengl_api_window.ClearBuffers();
			AliceUI::RenderImGui_API_OpenGL();
			opengl_api_window.SwapAndPoll();
		}

		opengl_api_window.Shutdown();
		opengl_api_window.~OpenGL();
	}

	// DirectX11 API Window
	if (Alice::API::CurrentRendererAPI == Alice::API::RendererAPI::DirectX)
	{
		HWND window = dx11_api_window.InitializeWindow(instance, cmd_show);
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* device_context = nullptr;
		IDXGISwapChain* swap_chain = nullptr;
		ID3D11RenderTargetView* render_target_view = nullptr;

		if (!dx11_api_window.InitializeDirectX(window, &device, &device_context, &swap_chain, &render_target_view))
			return 1;

		AliceUI::InitializeImGui_API_DirectX11(window, device, device_context);
		MSG msg{};

		while (Globals::m_bIsRunning)
		{
			while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (msg.message == WM_QUIT) Globals::m_bIsRunning = false;
			}

			if (!Globals::m_bIsRunning) break;

			AliceUI::SetupFrame_API_DirectX11();
			AliceUI::NewFrame();

			if (GetAsyncKeyState(VK_INSERT) & 1)
			{
				Globals::m_bIsVisible = !Globals::m_bIsVisible;
			}

			if (Globals::m_bIsVisible)
			{
				LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
				exStyle &= ~WS_EX_TRANSPARENT; // remove WS_EX_TRANSPARENT
				exStyle &= ~WS_EX_LAYERED; // remove WS_EX_LAYERED
				SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
			}
			else
			{
				LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
				exStyle |= WS_EX_TRANSPARENT; // add WS_EX_TRANSPARENT
				exStyle |= WS_EX_LAYERED; // add WS_EX_TRANSPARENT
				SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
			}

			if (Globals::m_bIsVisible)
			{
				RenderInterface();
			}

			const float color[4]{ 0.f, 0.f, 0.f, 0.f };
			device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
			device_context->ClearRenderTargetView(render_target_view, color);
			AliceUI::RenderImGui_API_DirectX11();

			swap_chain->Present(0U, 0U);
		}

		dx11_api_window.CleanUp(swap_chain, device, device_context, render_target_view, window, {});
		AliceUI::ShutdownImGui_API_DirectX11();
	}
}
