#pragma once

#include <pch.h>
#include "API.h"

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

#define OPENGL_API 0
#define DIRECTX11_API 1

namespace Globals
{
	//Alice::API::RendererAPI CheckAPI();
	inline bool m_bIsRunning = true;
	inline bool m_bIsVisible = true;
}