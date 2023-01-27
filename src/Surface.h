#pragma once
#include "vulkan/vulkan.h"
#include "export.h"

class VULKAN_WRAPPER_API Surface {
public:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
};
