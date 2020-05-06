#include "SandBox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{}

void SandBox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();
}

void SandBox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
	/*
	ImGui::Begin("Color Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
	*/
}

void SandBox2D::OnUpdate(Hazel::TimeStep ts)
{
	HZ_PROFILE_FUNCTION();

	// Update
	{
		HZ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		HZ_PROFILE_SCOPE("Renderer Preparation::OnUpdate");
		Hazel::RenderCommand::SetClearColor({ 0.9f, 0.5f, 0.6f, 1.0f });
		Hazel::RenderCommand::Clear();
	}

	{
		HZ_PROFILE_SCOPE("Renderer Draw::OnUpdate");

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Hazel::Renderer2D::DrawRotatedQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, glm::radians(45.0f), m_CheckerboardTexture, 10.0f), glm::vec4(1.0f, 0.4f, 0.4f, 1.0f);
		Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);

		Hazel::Renderer2D::EndScene();
	}
}

void SandBox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
