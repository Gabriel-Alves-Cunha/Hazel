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
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"
IncludeDir["stb_image"] = "Hazel/vendor/stb_image"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"

project "Hazel"
	location "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		--DOESNT NEED TO EXIST BECAUSE IS STATIC LIB
		-- postbuildcommands
		-- {
		-- 	--("powershell -command \"Start-Sleep -s 1\""),
		-- 	("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Hazel\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\bin\\Debug-x64\\Sandbox\" /Y /V /F"),
		-- 	--("powershell -command \"Start-Sleep -s 1\""),
		-- 	("xcopy \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Hazel\\Debug-windows-x86_64\\bin\\Hazel.dll\" \"C:\\Users\\gabri\\Documents\\Visual Studio 2019\\Projetos\\Game_Engine\\Sandbox\\Debug-windows-x86_64\\bin\" /Y /V /F")
		-- }

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_Release"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/MD"
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
		"Hazel/vendor",
		"%{IncludeDir.glm}"
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
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/MD"
		optimize "on"
