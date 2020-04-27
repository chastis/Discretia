project "Discretia"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   objdir "bin/obj/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp" }

   cppdialect "C++17"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"