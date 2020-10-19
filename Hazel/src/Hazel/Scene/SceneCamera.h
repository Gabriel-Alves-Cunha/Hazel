#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetViewPortSize(ui32 width, ui32 height);

		void SetOrthographicSize(float size)
			{ m_OrthographicSize = size; RecalculateProjection(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }

	private:
		void RecalculateProjection();

	private:
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar	= 1.0f;
		float m_AspectRatio = 0.0f;
	};
}
