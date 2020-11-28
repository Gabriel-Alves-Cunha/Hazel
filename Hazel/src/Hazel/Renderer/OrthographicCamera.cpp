#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Hazel
{
	OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // this order!
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		HZ_PROFILE_FUNCTION();

		m_ProjectionMatrix = ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		HZ_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), m_Position) * rotate(mat4(1.0f), radians(m_Rotation), vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // this order!
	}
} // namespace Hazel