#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(ui32 size);
		OpenGLVertexBuffer(float* vertices, ui32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, ui32 size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		ui32 m_RendererID;
		BufferLayout m_Layout;
	};

	// IndexBuffer ////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(ui32* indices, ui32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual ui32 GetCount() const { return m_Count; }

	private:
		ui32 m_RendererID;
		ui32 m_Count;
	};
}