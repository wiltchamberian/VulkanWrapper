#ifndef __LOGICAL_DEVICE_H
#define __LOGICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Common.h"
#include "PhysicalDevice.h"
#include <optional>
#include <vector>

class VULKAN_WRAPPER_API LogicalDevice {
public:
	bool isValid() const {
		return dev != VK_NULL_HANDLE;
	}
public:
	VkDevice dev = VK_NULL_HANDLE;
	PhysicalDevice phy_dev;
	QueueFamilyIndices indices_;
};

#endif 
