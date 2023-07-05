#ifndef __PHYSICAL_DEVICE_H
#define __PHYSICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Common.h"
#include <optional>

class LogicalDevice;
class Surface;

class VULKAN_WRAPPER_API PhysicalDevice {
public:
	bool isValid() {
		return (dev != VK_NULL_HANDLE);
	}
	LogicalDevice createLogicalDevice(VkQueueFlags flags, VkPhysicalDeviceFeatures features = {});
	bool isDeviceSuitable(VkQueueFlags flags, Surface surface);
	SwapChainSupportDetails querySwapChainSupport(Surface surface);
	VkPhysicalDevice& value() {
		return dev;
	}
private:
	VkPhysicalDevice dev = VK_NULL_HANDLE;
	QueueFamilyIndices indices;
	QueueFamilyIndices findQueueFamilies(VkQueueFlags flags, Surface surface);
};

#endif
