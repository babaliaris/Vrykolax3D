project "Sandbox"
    targetname "sandbox"
    language "C"
    cdialect "C99"

    includedirs {
        "src",
        "%{_WORKING_DIR}/Projects/Vrykolax3D/src/include/"
    }

    files {
        "src/**.c",
        "src/**.h"
    }

    links {
        "Vrykolax3D"
    }

    filter "platforms:PC"
        kind "ConsoleApp"
