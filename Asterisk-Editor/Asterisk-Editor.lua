project "Asterisk-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	staticruntime "off"
	flags { "MultiProcessorCompile" }

	targetdir ("bin/builds/%{cfg.system}/%{cfg.buildcfg}")
    objdir ("bin/intermediates/%{cfg.system}/%{cfg.buildcfg}")
	
	PrjLoc = "%{prj.location}/"

	-- preprocessors
	defines {
		
	}

	files {
		"**.lua",
		"editor/**.h",
		"editor/**.cpp",
	}

	includedirs {
		PrjLocation.. "editor",

        ThirdParty.SPDLOG,

		Projects.ASTERISK_ENGINE
	}

	links {
		"Asterisk-Engine"
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