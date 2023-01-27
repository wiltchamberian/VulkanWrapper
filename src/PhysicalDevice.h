#ifndef __PHYSICAL_DEVICE_H
#define __PHYSICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"
#include <optional>

class VULKAN_WRAPPER_API PhysicalDevice {
public:
	bool isValid() {
		return (dev != VK_NULL_HANDLE);
	}
	LogicalDevice createLogicalDevice(VkQueueFlags flags);
	bool isDeviceSuitable(VkQueueFlags flags);
	VkPhysicalDevice dev = VK_NULL_HANDLE;
	QueueFamilyIndices indices_;

private:
	QueueFamilyIndices findFamilyQueues(VkQueueFlags flags);
};

#endif
