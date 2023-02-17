#pragma once

#include "vulkan/vulkan.h"
#include "PhysicalDevice.h"

class VULKAN_WRAPPER_API VulkanInstance {
public:
	bool isValid() {
		return vk != VK_NULL_HANDLE;
	}
	VkInstance& value() {
		return vk;
	}
	PhysicalDevice selectPhysicalDevice(VkQueueFlags flags);
	
private:
	VkInstance vk = VK_NULL_HANDLE;
};
