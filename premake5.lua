-- premake5.lua
workspace "Discretia"
   location "Game"
   configurations { "Debug", "Release", "Dist" }
   architecture "x64"
   startproject "Discretia"
   platforms { "Win64" }

   flags { "MultiProcessorCompile", "FatalWarnings" }

   CPPDIALECT = "C++17"
   
   TARGET_DIR = "%{wks.location}/../bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
   OUTPUT_DIR = "%{wks.location}/../bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"

   DIST_TARGET_DIR = "%{wks.location}/../bin/dist"

   INCLUDE_PATHS = 
   {
      SFML = "%{wks.location}/SFML/include",
      ROOT = "%{wks.location}"
   }

   LIB_PATHS = 
    {
        SFML = "%{wks.location}/SFML/build/lib/%{cfg.buildcfg}",
        SFML_EXTLIB = "",

        SFML_DIST = "%{wks.location}/SFML/build/lib/Release"
    }

    filter "action:vs*"
        LIB_PATHS.SFML_EXTLIB = "%{wks.location}/SFML/extlibs/libs-msvc/x64"
        buildoptions {"/Zc:__cplusplus"}


   -- prebuildcommands 
   -- {
   --    "{COPY} %{wks.location}/SFML/build/lib/%{cfg.buildcfg} " .. TARGET_DIR,
   --    --TODO(maybe): make this compiler independent
   --    "{COPY} %{wks.location}/SFML/extlibs/libs-msvc/" .. "x" .. "%{cfg.architecture:sub(-2)} " .. TARGET_DIR,
   -- }

   filter "system:windows"
      systemversion "latest"
      defines {
         "M42_WINDOWS"
      }
   filter "configurations:Dist"
      postbuildcommands {
         "{COPY} %{wks.location}/Discretia/Content " .. DIST_TARGET_DIR .. "/Content",
         "{COPY} %{wks.location}/Discretia/Configs " .. DIST_TARGET_DIR .. "/Configs"
      }
   include "Game/Core"
   include "Game/Discretia"
