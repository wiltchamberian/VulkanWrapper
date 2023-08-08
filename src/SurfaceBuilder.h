#ifndef __SURFACE_BUILDER_H
#define __SURFACE_BUILDER_H

#include "export.h"
#include "Surface.h"
#include "vulkan/vulkan.h"
#include "Instance.h"

#ifdef _WIN32
#include "windows.h"
#include "vulkan/vulkan_win32.h"
#endif

#ifdef _WIN32
class VULKAN_WRAPPER_API SurfaceBuilder {
public:
	SurfaceBuilder(const VulkanInstance& instance, HINSTANCE hInstance, HWND hwnd);
	Surface build();
	SurfaceBuilder& setFlags(VkWin32SurfaceCreateFlagsKHR flags);
	SurfaceBuilder& setHINSTANCE(HINSTANCE hInstance);
	SurfaceBuilder& setHWND(HWND hwnd);
private:
	VkWin32SurfaceCreateInfoKHR khr;
	VulkanInstance instance;
};

#endif



#endif