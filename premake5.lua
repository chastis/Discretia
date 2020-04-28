-- premake5.lua
workspace "Discretia"
   location "Game"
   configurations { "Debug", "Release" }
   architecture "x64"
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

   include "Game/Core"
   include "Game/Discretia"
