-- premake5.lua
workspace "Discretia"
   location "Game"
   configurations { "Debug", "Release" }
   architecture "x64"
   startproject "Discretia"
   platforms { "Win64" }

   flags { "MultiProcessorCompile" }

   CPPDIALECT = "C++17"
   
   TARGET_DIR = "%{wks.location}/../bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
   OUTPUT_DIR = "%{wks.location}/../bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"

   INCLUDE_PATHS = 
   {
      SFML = "%{wks.location}/SFML/include",
      ROOT = "%{wks.location}"
   }

   prebuildcommands 
   {
      "{COPY} %{wks.location}/SFML/build/lib/%{cfg.buildcfg} " .. TARGET_DIR,
      --TODO(maybe): make this compiler independent
      "{COPY} %{wks.location}/SFML/extlibs/libs-msvc/" .. "x" .. "%{cfg.architecture:sub(-2)} " .. TARGET_DIR,
   }

   filter "system:windows"
      systemversion "latest"
      defines {
         "M42_WINDOWS"
      }
   filter "configurations:Release"
      postbuildcommands {
         "{COPY} %{wks.location}/Discretia/Content " .. TARGET_DIR .. "/Content",
         "{COPY} %{wks.location}/Discretia/Configs " .. TARGET_DIR .. "/Configs"
      }
   include "Game/Core"
   include "Game/Discretia"
