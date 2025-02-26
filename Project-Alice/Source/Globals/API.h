#pragma once
#include <pch.h>

namespace Alice
{
	namespace API
	{
		enum RendererAPI
		{
			OpenGL = 0,
			DirectX,
			Vulkan
		};

		inline RendererAPI CurrentRendererAPI = RendererAPI::OpenGL; // Default API
	}
}
