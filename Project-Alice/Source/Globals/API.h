#pragma once
#include <pch.h>

namespace Alice
{
	namespace API
	{
		enum RendererAPI
		{
			None = 0,
			OpenGL,
			DirectX,
			Vulkan
		};

		inline RendererAPI CurrentRendererAPI = RendererAPI::None;
	}
}
