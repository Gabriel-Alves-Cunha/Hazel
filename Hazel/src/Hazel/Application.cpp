#include "hzpch.h"
#include "Application.h"

#include "..\Hazel\Events\ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1000, 700);
		HZ_CORE_TRACE(e);

		while (true);
	}
}