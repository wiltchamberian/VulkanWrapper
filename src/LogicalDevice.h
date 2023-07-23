#ifndef __LOGICAL_DEVICE_H
#define __LOGICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Common.h"
#include "PhysicalDevice.h"
#include "DeviceQueue.h"
#include <optional>
#include <vector>

class Fence;
class FenceGroup;

class VULKAN_WRAPPER_API LogicalDevice {
public:
	friend class PhysicalDevice;
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
	void waitForFences(const FenceGroup& group, VkBool32 waitAll, uint64_t timeout);
	void waitForFence(const Fence& fence, VkBool32 waitAll, uint64_t timeout);
	void resetFences(const FenceGroup& group);
	void waitIdle();
private:
	VkDevice dev = VK_NULL_HANDLE;
	PhysicalDevice phy_dev;
	QueueFamilyIndices indices;
};

#endif 
