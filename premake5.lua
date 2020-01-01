workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{prj.name}/" .. outputdir .. "/bin")
	objdir ("%{prj.name}/" .. outputdir .. "/bin-int")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}
	
		postbuildcommands
		{
			("powershell -command \"Start-Sleep -s 2\""),
			("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Hazel\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Sandbox\" /Y /V /F"),
			("powershell -command \"Start-Sleep -s 2\""),
			("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\Debug-windows-x86_64\\bin\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Sandbox\\Debug-windows-x86_64\\bin\" /Y /V /F")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"