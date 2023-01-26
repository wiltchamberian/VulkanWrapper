#pragma once

#ifdef VULKANWRAPPER_EXPORTS
#define VULKAN_WRAPPER_API  _declspec(dllexport)
#else 
#define VULKAN_WRAPPER_API _declspec(dllimport)
#endif 
