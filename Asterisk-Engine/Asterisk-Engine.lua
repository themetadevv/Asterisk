
--[[
    Asterisk-Engine Project Generation Premake5 Script
    Project Info {
        Language: C++ 23
        Kind: Static/Shared
    }
]]

project "Asterisk-Engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"
    flags { "MultiProcessorCompile" }

    targetdir ("bin/build/%{cfg.system}/%{cfg.buildcfg}")
    objdir ("bin/intermediates/%{cfg.system}/%{cfg.buildcfg}")

    PrjLocation = "%{prj.location}/"
    
    pchheader "astpch.h"
    pchsource "astpch.cpp"

    postbuildcommands {
         -- to exports dir
		'{MKDIR}    "%{wks.location}/Exports/%{cfg.buildcfg}_%{cfg.system}/"',
		'{COPYFILE} "%{cfg.buildtarget.abspath}" "%{wks.location}/Exports/%{cfg.buildcfg}_%{cfg.system}/"',

        -- to editor proj dir
		'{MKDIR}    "%{wks.location}/Asterisk-Editor/bin/builds/%{cfg.system}/%{cfg.buildcfg}"', 
		'{COPYFILE} "%{cfg.buildtarget.abspath}" "%{wks.location}/Asterisk-Editor/bin/builds/%{cfg.system}/%{cfg.buildcfg}"'
	}

    -- preprocessors
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    files {
        "**.lua",
        "**.h",
        "**.cpp"
    }

    includedirs {
        -- this Project
        PrjLocation,
        PrjLocation.. "src",

        -- header only
        ThirdParty.SPDLOG,
        ThirdParty.IMGUI,
        
        -- compiled
        ThirdParty.GLFW,
        ThirdParty.GLAD
    }

    links {
        "glfw",
        "glad",
        "imgui"
    }

    -- kind
    filter "kind:SharedLib"
        defines {
            "BUILD_SHARED"
        }
    filter {}

    filter "kind:StaticLib"
        defines {
            "BUILD_STATIC"
        }
    filter {}

    -- platform
    filter "system:windows"
        systemversion "latest"
        defines { 
            "PLATFORM_WINDOWS"
        }
    filter {}

    -- debug configuration
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        optimize "off"
        buildoptions { "/utf-8"}

        defines {
            "DEBUG_BUILD"
        }
    filter {}

    -- release configuration
    filter "configurations:Release"
        runtime "Release"
        symbols "off" -- 'on' for debugging release crashes
        optimize "on"
        buildoptions { "/utf-8"}

        defines {
            "RELEASE_BUILD"
        }
    filter {}
