#pragma once

#include "Hazel/Renderer/OrtographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	struct OrtographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrtographicCameraController
	{
	public:
		OrtographicCameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		void OnResize(float w, float h);

		OrtographicCamera& GetCamera() { return m_Camera; }
		const OrtographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }

		const OrtographicCameraBounds& GetBounds() const { return m_Bounds; }

	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrtographicCameraBounds m_Bounds;
		OrtographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 90.0f;
	};

}