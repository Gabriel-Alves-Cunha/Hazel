#include "hzpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar  = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewPortSize(ui32 width, ui32 height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
		float orthoRight = -orthoLeft;
		float orhtoBottom = -m_OrthographicSize * 0.5f;
		float orthoTop = -orhtoBottom;

		m_Projection = glm::ortho(orthoLeft, orthoRight, orhtoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}
