-- premake5.lua
workspace "Discretia"
   configurations { "Debug", "Release" }

   flags { "MultiProcessorCompile" }

   include "Discretia"
