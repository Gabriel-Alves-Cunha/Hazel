#pragma once

#include "Hazel/Renderer/FrameBuffer.h"

namespace Hazel
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void Resize(ui32 width, ui32 height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		virtual const FrameBufferSpec& GetSpec() const override { return m_Spec; }

	private:
		ui32 m_RendererID = 0,
		m_ColorAttachment = 0,
		m_DepthAttachment = 0;

		FrameBufferSpec m_Spec;
	};
}