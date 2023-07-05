#pragma once
#include "vulkan/vulkan.h"
#include "export.h"
#include "Instance.h"

class VULKAN_WRAPPER_API Surface {
public:
	friend class SurfaceBuilder;
	bool isValid() const {
		return surface != VK_NULL_HANDLE;
	}
	VkSurfaceKHR& value() {
		return surface;
	}
	void cleanUp();
private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VulkanInstance instance;
};
