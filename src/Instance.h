#pragma once

#include "export.h"
#include "vulkan/vulkan.h"
#include "PhysicalDevice.h"

typedef bool (*PhysicalDeviceFilter)(VkPhysicalDeviceProperties& properties, VkPhysicalDeviceFeatures& features);


class VULKAN_WRAPPER_API VulkanInstance {
public:
	bool isValid() {
		return vk != VK_NULL_HANDLE;
	}
	VkInstance& value() {
		return vk;
	}
	PhysicalDevice selectPhysicalDevice(VkQueueFlags flags, PhysicalDeviceFilter = nullptr);
	void clearUp();
private:
	PhysicalDeviceFilter filter = nullptr;
	VkInstance vk = VK_NULL_HANDLE;
};
