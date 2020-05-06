#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	//Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, static_cast<int32_t>(key));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}