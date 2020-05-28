project "Discretia"
   location ""
   language "C++"
   cppdialect (CPPDIALECT)
   targetdir (TARGET_DIR)
   objdir (OUTPUT_DIR .. "/%{prj.name}")

   files { "**.hpp", "**.cpp" }

   includedirs
   {
      INCLUDE_PATHS.ROOT,
      INCLUDE_PATHS.SFML
   }
   libdirs {
      LIB_PATHS.SFML
   }

   links {
      "Core"
   }

   defines {
      "M42_DISCRETIA"
   }

   filter "configurations:Debug"
      kind "ConsoleApp"
      defines { "DEBUG" }
      symbols "On"
      runtime "Debug"

   filter "configurations:Release or Dist"
      kind "WindowedApp"
      defines { "NDEBUG"}
      optimize "On"
      runtime "Release"

      links {
         "sfml-main"
      }

   filter "configurations:Release"
      defines { "RELEASE" }
   
   filter "configurations:Dist"
      targetdir (DIST_TARGET_DIR)
      libdirs { LIB_PATHS.SFML_DIST }
      defines
      {
          "DIST"
      }
