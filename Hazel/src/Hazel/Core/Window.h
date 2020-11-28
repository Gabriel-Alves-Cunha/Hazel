#pragma once

#include <sstream>

#include "hzpch.h" // ui32

#include "Hazel/Core/Base.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{

	struct WindowProps
	{
		std::string Title;
		ui32 Width;
		ui32 Height;

		WindowProps(const std::string& title = "Hazel Engine",
			ui32 width = 1280,
			ui32 height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual ui32 GetWidth() const = 0;
		virtual ui32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}