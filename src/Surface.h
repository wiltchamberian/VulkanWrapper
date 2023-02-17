#pragma once
#include "vulkan/vulkan.h"
#include "export.h"

class VULKAN_WRAPPER_API Surface {
public:
	bool isValid() const {
		return surface != VK_NULL_HANDLE;
	}
	VkSurfaceKHR& value() {
		return surface;
	}
private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
};
