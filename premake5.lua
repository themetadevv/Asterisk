workspace "Asterisk"
	architecture "x64"
	configurations {"Debug", "Release", "Profile"}
	startproject "Asterisk-Editor"

WorkspaceDir  = "%{wks.location}/"
ExportDir     = "%{wks.location}/Exports/%{cfg.buildcfg}_%{cfg.system}/"
ThirdPartyDir = "%{wks.location}/ThirdParty/"

-- include dirs
ThirdParty = {
	GLFW        = ThirdPartyDir.. "glfw/include",
	GLAD        = ThirdPartyDir.. "glad/include",
	IMGUI       = ThirdPartyDir.. "imgui",
	SPDLOG      = ThirdPartyDir.. "spdlog/include"
}

Projects = {
	ASTERISK_ENGINE = WorkspaceDir.. "Asterisk-Engine/src"
}

-- ===== Group: Vendors =====
group "ThirdParties"
	include "ThirdParty/glfw"
	include "ThirdParty/glad"
	include "ThirdParty/imgui"
group ""

-- ===== Group: Projects =====
group "Projects"
	include "Asterisk-Engine/Asterisk-Engine.lua"
	include "Asterisk-Editor/Asterisk-Editor.lua"
group ""

-- ===== Group: Applications =====