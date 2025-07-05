project "Vrykolax3D"

    -- ================|Cross Platform Options|================ --
    language "C"
    cdialect "C99"

    includedirs {
        "src/include/"
    }

    files {
            "src/source/core/**.c",
            "src/include/vrykolax3D/core/**.h"
    }
    -- ================|Cross Platform Options|================ --


    -- ======================|PC Options|====================== --
    filter "platforms:pc_shared or pc_static"
        files {
            "src/source/platform/pc/**.c",
            "src/include/vrykolax3D/platform/pc/**.h"
        }
    -- ======================|PC Options|====================== --

    -- Shared Library.
    filter "platforms:pc_shared"
        kind "SharedLib"
        defines "VX3D_SHARED_LIB"

    --Static Library.
    filter "platforms:pc_static"
        kind "StaticLib"
        defines "VX3D_STATIC_LIB"
