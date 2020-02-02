#pragma once

#include <Hazel/Core.h>
#include <Hazel/KeyCodes.h>
#include <Hazel/Core/MouseCodes.h>

namespace Hazel
{
	class Input
	{
	protected:
		Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

		static Scope<Input> Create();

	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;

		virtual std::pair<float, float> GetMousePosImpl() = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};
}