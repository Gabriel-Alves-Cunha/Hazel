#include "hzpch.h"
#include "FrameBuffer.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hazel
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None  : HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
