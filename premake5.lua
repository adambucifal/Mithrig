newoption {
    trigger     = "mayaversion",
    value       = "VERSION",
    description = "Choose a target maya version: 2024, 2025, 2026, etc"
}

MAYA_VERSION = _OPTIONS["mayaversion"] or "2026"

if os.target() == "windows" then
    MAYA_LOCATION = "C:/Program Files/Autodesk/"
elseif os.target() == "macosx" then
    MAYA_LOCATION = "/Applications/Autodesk/"
elseif os.target() == "linux" then
    MAYA_LOCATION = "/usr/autodesk/"
end

MAYA_LOCATION = path.join(MAYA_LOCATION, "Maya" .. MAYA_VERSION)
MAYA_INCLUDE = path.join(MAYA_LOCATION, "include")
MAYA_LIB = path.join(MAYA_LOCATION, "lib")
MAYA_MODULES = path.join(MAYA_LOCATION, "modules")

MAYA_PLUGIN_ROOT = path.join(MAYA_LOCATION, "plug-ins", "Mithrig")
MAYA_PLUGIN_MLL_PATH = path.join(MAYA_PLUGIN_ROOT, "plug-ins")


EXTERNAL_INCLUDE = "external/include"

DEF_DEBUG = "MITHRIG_DEBUG"
DEF_RELEASE = "MITHRIG_RELEASE"
DEF_DIST = "MITHRIG_DIST"

OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- ======================== Solution Setup ========================
workspace "Mithrig"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }


project "Utilities"
    location "source/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
        "source/%{prj.name}/**.h",
        "source/%{prj.name}/**.cpp",
    }

    vpaths {
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
    }

    includedirs {
        MAYA_INCLUDE,
        EXTERNAL_INCLUDE,
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "off"

    filter "configurations:Debug" 
        defines {DEF_DEBUG}
        symbols "On"

    filter "configurations:Release" 
        defines {DEF_RELEASE}
        optimize "On"
    
    filter "configurations:Dist" 
        defines {DEF_DIST}
        optimize "On"


project "Core"
    location "source/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
        "source/%{prj.name}/**.h",
        "source/%{prj.name}/**.cpp",
    }

    vpaths {
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
    }

    includedirs {
        MAYA_INCLUDE,
        EXTERNAL_INCLUDE,
		"source/Utilities"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "off"

    filter "configurations:Debug" 
        defines {DEF_DEBUG}
        symbols "On"

    filter "configurations:Release" 
        defines {DEF_RELEASE}
        optimize "On"
    
    filter "configurations:Dist" 
        defines {DEF_DIST}
        optimize "On"


project "Commands"
    location "source/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
        "source/%{prj.name}/**.h",
        "source/%{prj.name}/**.cpp",
    }

    vpaths {
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
    }

    includedirs {
        MAYA_INCLUDE,
        EXTERNAL_INCLUDE,
        "source/Core",
        "source/Utilities"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "off"

    filter "configurations:Debug"
        defines {DEF_DEBUG}
        symbols "On"

    filter "configurations:Release"
        defines {DEF_RELEASE}
        optimize "On"

    filter "configurations:Dist"
        defines {DEF_DIST}
        optimize "On"


project "Plugin"
    location "source/%{prj.name}"
    kind "SharedLib"
    language "C++"

    targetname "Mithrig"

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
        "source/%{prj.name}/**.h",
        "source/%{prj.name}/**.cpp",
    }

    vpaths {
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
    }

    includedirs {
        MAYA_INCLUDE,
        EXTERNAL_INCLUDE,
        "source/Core",
		"source/Commands"
    }

    libdirs {
        MAYA_LIB
    }

    links {
        "OpenMaya",
        "OpenMayaAnim",
        "OpenMayaUI",
        "Qt6Core",
        "Foundation",
        "Core",
		"Commands"
    }

    postbuildcommands {
        '{MKDIR} "' .. MAYA_MODULES .. '"',
        '{COPY} "%{wks.location}scripts/Mithrig.mod" "' .. MAYA_MODULES .. '"',
        '{MKDIR} "' .. MAYA_PLUGIN_MLL_PATH .. '"',
        '{COPY} "%{cfg.buildtarget.abspath}" "' .. MAYA_PLUGIN_MLL_PATH .. '"',
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "off"
        targetextension ".mll"

    filter "system:linux"
        targetextension ".so"

    filter "system:macosx"
        targetextension ".bundle"

    filter "configurations:Debug" 
        defines {DEF_DEBUG}
        symbols "On"

    filter "configurations:Release" 
        defines {DEF_RELEASE}
        optimize "On"
    
    filter "configurations:Dist" 
        defines {DEF_DIST}
        optimize "On"

