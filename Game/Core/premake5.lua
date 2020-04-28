project "Core"
   location ""
   kind "StaticLib"
   language "C++"
   cppdialect (CPPDIALECT)
   targetdir (TARGET_DIR)
   objdir (OUTPUT_DIR .. "/%{prj.name}")

   files 
   {
      "**.cpp"
      , "**.h"
   }

   includedirs
   {
      INCLUDE_PATHS.ROOT,
      INCLUDE_PATHS.SFML
   }
   libdirs {
      TARGET_DIR
   }

   links {
      "opengl32",
      "freetype",
      "winmm",
      "gdi32",
      "flac",
      "vorbisenc",
      "vorbisfile",
      "vorbis",
      "ogg",
      "ws2_32",
   }

   defines {
        "M42_CORE"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      runtime "Debug"

      links {
         "sfml-graphics-d",
         "sfml-window-d",
         "sfml-system-d",
         "sfml-audio-d",
         "sfml-network-d"
      }

   filter "configurations:Release"
      defines { "NDEBUG", "RELEASE"}
      optimize "On"
      runtime "Release"
      links {    
         "sfml-graphics",
         "sfml-window",
         "sfml-system",
         "sfml-audio",
         "sfml-network"
      }
