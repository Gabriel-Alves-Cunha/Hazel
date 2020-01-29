#include "hzpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
}