#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "SandBox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new SandBox2D());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
