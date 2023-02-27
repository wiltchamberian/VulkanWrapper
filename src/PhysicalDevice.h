#ifndef __PHYSICAL_DEVICE_H
#define __PHYSICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Surface.h"
#include "Common.h"
#include <optional>

class LogicalDevice;

class VULKAN_WRAPPER_API PhysicalDevice {
public:
	bool isValid() {
		return (dev != VK_NULL_HANDLE);
	}
	LogicalDevice createLogicalDevice(VkQueueFlags flags);
	bool isDeviceSuitable(VkQueueFlags flags);
	SwapChainSupportDetails querySwapChainSupport(Surface surface);
	VkPhysicalDevice& value() {
		return dev;
	}
private:
	VkPhysicalDevice dev = VK_NULL_HANDLE;
	QueueFamilyIndices indices_;
	QueueFamilyIndices findQueueFamilies(VkQueueFlags flags);
};

#endif
