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
      TARGET_DIR
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

   filter "configurations:Release"
      kind "WindowedApp"
      defines { "NDEBUG", "RELEASE"}
      optimize "On"
      runtime "Release"

      links {
         "sfml-main"
      }