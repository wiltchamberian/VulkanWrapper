#pragma once

#include "vulkan/vulkan.h"
#include "PhysicalDevice.h"

class VULKAN_WRAPPER_API VulkanInstance {
public:
	bool isempty() {
		return vk == VK_NULL_HANDLE;
	}
	PhysicalDevice selectPhysicalDevice(VkQueueFlags flags);
	VkInstance vk = VK_NULL_HANDLE;
private:
	bool isDeviceSuitable(PhysicalDevice& dev, VkQueueFlags flags);
};
