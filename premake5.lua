workspace "imguiWindow"
	architecture "x64"
	startproject "imguiWindow"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-$%{cfg.architecture}"
-- Include directories relative to the root folder
IncludeDir = {}
IncludeDir["GLFW"] = "imguiWindow/vendor/GLFW/include"
IncludeDir["glad"] = "imguiWindow/vendor/glad/include"
IncludeDir["ImGui"] = "imguiWindow/vendor/imgui"
IncludeDir["glm"] = "imguiWindow/vendor/glm"

include "imguiWindow/vendor/GLFW"
include "imguiWindow/vendor/glad"
include "imguiWindow/vendor/imgui"

project "imguiWindow"
	location "imguiWindow"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "imguiWindow/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		buildoptions "/MD"
		optimize "On"
