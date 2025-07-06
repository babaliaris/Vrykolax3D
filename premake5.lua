workspace "Vrykolax3D"
    platforms {"pc_shared", "pc_static"}
    configurations {"debug", "release", "dist"}
    startproject "Sandbox"
    targetdir "build/%{cfg.shortname}"
    objdir "%{_WORKING_DIR}/obj/%{cfg.shortname}/%{prj.name}"

    -- PC Platform ALL CONFIGURATIONS.
    filter "platforms:pc_shared or pc_static"
        defines {"VX3D_PLATFORM_PC"}

    -- PC DEBUG
    filter {"platforms:pc_shared or pc_static", "configurations:debug"}
        symbols "On"
        optimize "Off"
        defines {"VX3D_DEBUG_ON"}

    -- PC RELEASE
    filter {"platforms:pc_shared or pc_static", "configurations:release"}
        symbols "On"
        optimize "Off"
        defines {"VX3D_RELEASE_ON"}

    -- PC DIST
    filter {"platforms:pc_shared or pc_static", "configurations:dist"}
        symbols "Off"
        optimize "Off"
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
