workspace "MinigameEditor"
    configurations {"Debug","Release"}
    filter "configurations:Debug"
        defines {"DEBUG"}
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
project "MinigameEditor"
    kind "ConsoleApp"
    language "C"
    files{
        "*.c",
        "*.h"
    }
    
    filter "system:windows"
       system("windows")
       architecture "x64"
       libdirs{
        "deps/SDL3/lib/x64",
        "deps/Lua5.1/lib/x64/"
       }
       includedirs{
        "deps/SDL3/include",
        "deps/Lua5.1/include"
       }
       links{"SDL3","Lua51_x64-Release"}
