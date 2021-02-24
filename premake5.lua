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

    links {
        "SDL2",
        "GLEW",
        "GL"
    }