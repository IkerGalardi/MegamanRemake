workspace "megaman"
    architecture "x64"
    configurations {"Debug", "Release"}
    flags {"MultiProcessorCompile"}

project "megaman"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/")
    objdir("bin/obj/")

    files { "src/**.cc", "src/**.hh" }
    includedirs {"lib/include", "src"}

    libdirs {"lib/bin"}
    links {
        "SDL2",
        "GLEW",
        "GL", 
        "box2d"
    }
    
    filter "configurations:Debug"
        symbols "on"
        optimize "off"
    filter "configurations:Release"
        symbols "off"
        optimize "on"
        runtime "Release"