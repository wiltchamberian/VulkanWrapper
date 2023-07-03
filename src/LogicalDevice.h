#ifndef __LOGICAL_DEVICE_H
#define __LOGICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Common.h"
#include "PhysicalDevice.h"
#include "DeviceQueue.h"
#include <optional>
#include <vector>

class VULKAN_WRAPPER_API LogicalDevice {
public:
	bool isValid() const {
		return dev != VK_NULL_HANDLE;
	}
	VkDevice& value() {
		return dev;
	}
	PhysicalDevice& physical_device() {
		return phy_dev;
	}
	void cleanUp();
	DeviceQueue getDeviceQueue(VkQueueFlags que, int index = 0);
public:
	VkDevice dev = VK_NULL_HANDLE;
	PhysicalDevice phy_dev;
	QueueFamilyIndices indices;
};

#endif 
