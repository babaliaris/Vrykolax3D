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
    filter "platforms:PC"
        kind (
            (_OPTIONS["libtype"] == nil or _OPTIONS["libtype"] == "shared")
            and "SharedLib" or "StaticLib"
        )

        files {
            "src/source/platform/pc/**.c",
            "src/include/vrykolax3D/platform/pc/**.h"
        }

        defines "VX3D_STATIC_LIB"
    -- ======================|PC Options|====================== --
