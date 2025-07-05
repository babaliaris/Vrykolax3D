workspace "Vrykolax3D"
    platforms {"pc"}
    configurations {"debug", "release", "dist"}
    startproject "Sandbox"
    targetdir "build/%{cfg.shortname}"
    objdir "%{_WORKING_DIR}/obj/%{cfg.shortname}/%{prj.name}"

    -- Add Static or Shared lib type option. 
    newoption {
        trigger = "libtype",
        value = "TYPE",
        description = "Choose which type of library to build",
        allowed = {
            { "static", "Build Static Library" },
            { "shared", "Build Shared Library" }
        }
    }

    -- PC Platform ALL CONFIGURATIONS.
    filter "platforms:PC"
        defines {"VX3D_PLATFORM_PC"}

    -- PC DEBUG
    filter {"platforms:PC", "configurations:debug"}
        symbols "On"
        optimize "Off"
        defines {"VX3D_DEBUG_ON"}

    -- PC RELEASE
    filter {"platforms:PC", "configurations:release"}
        symbols "Off"
        optimize "On"
        defines {"VX3D_RELEASE_ON"}

    -- PC DIST
    filter {"platforms:PC", "configurations:dist"}
        symbols "Off"
        optimize "On"
        defines {"VX3D_DIST_ON"}

    -- Diselect all filters.
    filter {}

    -- Linux ALL CONFIGURATIONS.
    filter "system:linux"
        defines {"VX3D_OS_LINUX"}

    -- Windows ALL CONFIGURATIONS.
    filter "system:windows"
        defines {"VX3D_OS_WINDOWS"}

    -- MacosX ALL CONFIGURATIONS.
    filter "system:macosx"
        defines {"VX3D_OS_MACOSX"}

    include "Projects/Vrykolax3D/vrykolax3d.lua"
    include "Projects/VampTest/vamptest.lua"
    include "Projects/Sandbox/sandbox.lua"
