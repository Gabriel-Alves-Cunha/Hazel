#pragma once

#include "Camera.h"
#include "OrtographicCamera.h"
#include "Texture.h"

namespace Hazel
{
class Renderer2D
{
public:
	static void Init();
	static void Shutdown();

	static void BeginScene(const Camera &camera, const glm::mat4& transform);
	static void BeginScene(const OrtographicCamera &camera);
	static void EndScene();
	static void Flush();

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	// Primitives
	static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);

	static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

	static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

	static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
///////////////////////////////////////////////////////////////////
	static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);

	static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);

	static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	// Stats
	struct Statistics
	{
		ui32 DrawCalls = 0;
		ui32 QuadCount = 0;

		ui32 GetTotalVertexCount() { return QuadCount * 4; }
		ui32 GetTotalIndexCount() { return QuadCount * 6; }
	};

	static void ResetStats();
	static Statistics GetStats();

private:
	static void FlushAndReset();
};
} // namespace Hazel
