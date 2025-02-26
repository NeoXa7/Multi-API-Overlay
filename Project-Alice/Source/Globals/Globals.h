#pragma once

#include <pch.h>
#include "API.h"

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define DIRECTX11_API "DirectX11"
#define OPENGL_API "OpenGL"

namespace Globals
{
	Alice::API::RendererAPI CheckAPI();
	inline bool m_bIsRunning = true;
	inline bool m_bIsVisible = true;
}