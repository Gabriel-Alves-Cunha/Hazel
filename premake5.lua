workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		--"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("%{prj.name}/" .. outputdir .. "/bin")
	objdir ("%{prj.name}/" .. outputdir .. "/bin-int")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		postbuildcommands
		{
			--("powershell -command \"Start-Sleep -s 1\""),
			("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Hazel\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Sandbox\" /Y /V /F"),
			--("powershell -command \"Start-Sleep -s 1\""),
			("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\Debug-windows-x86_64\\bin\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Sandbox\\Debug-windows-x86_64\\bin\" /Y /V /F")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		--runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_Release"
		buildoptions "/MD"
		--runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		--runtime "Release"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{prj.name}/" .. outputdir .. "/bin")
	objdir ("%{prj.name}/" .. outputdir .. "/bin-int")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"Hazel/vendor"
	}

	links
	{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		--runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		--runtime "Release"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		--runtime "Release"
		buildoptions "/MD"
		optimize "on"


project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{--C:\Users\gabri\Documents\Visual Studio 2019\Projetos\Game_Engine\Hazel\vendor\GLFW\src\context.c
		"Hazel/vendor/%{prj.name}/include/GLFW/glfw3.h",
		"Hazel/vendor/%{prj.name}/include/GLFW/glfw3native.h",
		"Hazel/vendor/%{prj.name}/src/glfw_config.h",
		"Hazel/vendor/%{prj.name}/src/context.c",
		"Hazel/vendor/%{prj.name}/src/init.c",
		"Hazel/vendor/%{prj.name}/src/input.c",
		"Hazel/vendor/%{prj.name}/src/monitor.c",
		"Hazel/vendor/%{prj.name}/src/vulkan.c",
		"Hazel/vendor/%{prj.name}/src/window.c"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "on"

		files
		{
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/x11_init.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/x11_monitor.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/x11_window.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/xkb_unicode.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/posix_time.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/posix_thread.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/glx_context.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/egl_context.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/osmesa_context.c",
			"Hazel/vendor/%{prj.name}/Hazel/vendor/%{prj.name}/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

		files
		{
			"Hazel/vendor/%{prj.name}/src/win32_init.c",
			"Hazel/vendor/%{prj.name}/src/win32_joystick.c",
			"Hazel/vendor/%{prj.name}/src/win32_monitor.c",
			"Hazel/vendor/%{prj.name}/src/win32_time.c",
			"Hazel/vendor/%{prj.name}/src/win32_thread.c",
			"Hazel/vendor/%{prj.name}/src/win32_window.c",
			"Hazel/vendor/%{prj.name}/src/wgl_context.c",
			"Hazel/vendor/%{prj.name}/src/egl_context.c",
			"Hazel/vendor/%{prj.name}/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MD"
		optimize "on"

project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"