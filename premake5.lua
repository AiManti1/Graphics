workspace "Mantle"
	architecture "x64"
	startproject "OClient"
	configurations { "Debug", "Release", "Distribution" }

	-- variables: build configuration -- system(win or mac etc.) -- architecture
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 --Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Mantle/Extlib/GLFW/include"
	IncludeDir["Glad"] = "Mantle/Extlib/Glad/include"
	IncludeDir["ImGui"] = "Mantle/Extlib/imgui"
	IncludeDir["glm"] = "Mantle/Extlib/glm"

	group "Extlib Dependencies"
		include "Mantle/Extlib/GLFW" -- Include GLFW's premake file for compilation and link it to Mantle project
		include "Mantle/Extlib/Glad"
		include "Mantle/Extlib/imgui"
	group ""

-- project "Mantle" corresponds to the project inside the VS Solution
project "Mantle"
	location "Mantle"						-- Everything will be relative to this folder
	kind "SharedLib"						-- Means it is dynamic lib
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- see above variables
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtlpch.h"					-- use pch
	pchsource "Mantle/Source/mtlpch.cpp"	-- create pch 

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Extlib/glm/glm/**.hpp",
		"%{prj.name}/Extlib/glm/glm/**.inl"
	}
	
	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Extlib/spdlog/include",
		"%{IncludeDir.GLFW}",				-- means "Mantle/Extlib/GLFW/include
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MTL_PLATFORM_WINDOWS",
			"MTL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/OClient/\"") }

	filter "configurations:Debug"
		defines "MTL_DEBUG"
		runtime "Debug"						-- buildoptions "/MDd" -- multithreaded Debug DLL
		symbols "On"

	filter "configurations:Release"
		defines "MTL_RELEASE"
		runtime "Release"					-- static runtime for non-DLL -- buildoptions "/MD" -- multithreaded DLL for the C++ RunTime library 
		optimize "On"

	filter "configurations:Distribution"
		defines "MTL_DISTRIB"
		runtime "Release"					-- buildoptions "/MD" -- multithreaded DLL
		optimize "On"

		-- OClient project
project "OClient"
	location "OClient"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Mantle/Source",
		"Mantle/Extlib/spdlog/include",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mantle"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MTL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MTL_DEBUG"
		runtime "Debug"						-- buildoptions "/MDd"	-- multithreaded Debug DLL
		symbols "On"

	filter "configurations:Release"
		defines "MTL_RELEASE"
		runtime "Release"					-- buildoptions "/MD"	-- multithreaded DLL
		optimize "On"

	filter "configurations:Distribution"
		defines "MTL_DISTRIB"
		runtime "Release"					-- buildoptions "/MD"	-- multithreaded DLL
		optimize "On"