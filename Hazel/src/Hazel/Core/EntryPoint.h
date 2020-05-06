#pragma once

#include "Core.h"

#ifdef HZ_PLATFORM_WINDOWS

	extern Hazel::Application*	Hazel::CreateApplication();

	int main(int argc, char** argv)
	{
		Hazel::Log::Init();

		HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfil-Startup.json");
		auto app = Hazel::CreateApplication();
		HZ_PROFILE_END_SESSION();

		HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfil-Runtime.json");
		app->Run();
		HZ_PROFILE_END_SESSION();

		HZ_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfil-Shutdown.json");
		delete app;
		HZ_PROFILE_END_SESSION();

		return 0;
	}
#endif