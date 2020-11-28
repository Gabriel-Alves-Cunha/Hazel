#include "hzpch.h"
#include "Hazel/Renderer/Renderer2D.h"

#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Hazel
{
	struct QuadVertex
	{
		vec3 Position;
		vec4 Color;
		vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const ui32 MAX_QUADS = 20000;
		static const ui32 MAX_VERTICES = MAX_QUADS * 4;
		static const ui32 MAX_INDICES = MAX_QUADS * 6;
		static const ui32 MAX_TEXTURES_SLOT = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		ui32 QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MAX_TEXTURES_SLOT> TextureSlots;
		ui32 TextureSlotIndex = 1; // 0 = white texture

		vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MAX_VERTICES * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MAX_VERTICES];

		ui32* quadIndices = new ui32[s_Data.MAX_INDICES];

		ui32 offset = 0;
		for (ui32 i = 0; i < s_Data.MAX_INDICES; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MAX_INDICES);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

		delete[] quadIndices;


		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		ui32 whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(ui32));

		i32 samplers[s_Data.MAX_TEXTURES_SLOT];
		for (uint32_t i = 0; i < s_Data.MAX_TEXTURES_SLOT; ++i)
			samplers[i] = i;

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MAX_TEXTURES_SLOT);

		// Set first texture slot to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		HZ_PROFILE_FUNCTION();

		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}
	
		void Renderer2D::BeginScene(const Camera& camera, const mat4& transform)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		HZ_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer2D::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing to draw

		ui32 dataSize = (ui32)((ui8*)s_Data.QuadVertexBufferPtr - (ui8*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexbuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		// Bind textures
		for (ui32 i = 0; i < s_Data.TextureSlotIndex; ++i)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}
	
	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}
	
	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	
		void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		mat4 transform = glm::translate(mat4(1.0f), position)
			* glm::scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}
	
		void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();

		mat4 transform = glm::translate(mat4(1.0f), position)
			* glm::scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const mat4& transform, const vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= Renderer2DData::MAX_INDICES)
			NextBatch();

		for (size_t i = 0; i < quadVertexCount; ++i)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MAX_INDICES)
			NextBatch();

		float textureIndex = 0.0f;
		for (ui32 i = 1; i < s_Data.TextureSlotIndex; ++i)
			if (*s_Data.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MAX_TEXTURES_SLOT)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;

			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;

			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; ++i)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}
	
	// rotation is in radians!!!
	
	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), position)
			* rotate(mat4(1.0f), radians(rotation), { 0.0f, 0.0f, 1.0f })
			* scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();

		mat4 transform = glm::translate(mat4(1.0f), position)
			* rotate(mat4(1.0f), radians(rotation), { 0.0f, 0.0f, 1.0f })
			* scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
} // namespace Hazel