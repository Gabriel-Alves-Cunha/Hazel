#pragma once

#include "Hazel/Core/Base.h"

namespace Hazel
{
	struct FrameBufferSpec
	{
		ui32 width = 0, height = 0, samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual ui32 GetColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpec& GetSpec() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpec& spec);
	};
}