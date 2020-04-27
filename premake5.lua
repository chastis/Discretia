-- premake5.lua
workspace "Discretia"
   configurations { "Debug", "Release" }

   
   flags { "MultiProcessorCompile" }

project "Discretia"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp" }

   cppdialect "C++17"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"