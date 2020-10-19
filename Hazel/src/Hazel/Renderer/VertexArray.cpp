#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		HZ_CORE_ASSERT(false, "No RendererAPI selected.");
		return nullptr;
	}
}