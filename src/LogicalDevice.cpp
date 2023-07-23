#include "LogicalDevice.h"
#include "Fence.h"
#include <stdexcept>

void LogicalDevice::cleanUp() {
	if (dev) {
		vkDestroyDevice(dev, nullptr);
		dev = VK_NULL_HANDLE;
	}
	return;
}

DeviceQueue LogicalDevice::getDeviceQueue(VkQueueFlags que, int index) {
	DeviceQueue deviceQue;
	int ds = 1;
	const int queueFlagsBitsNum = 8;
	for(int i =0; i< queueFlagsBitsNum;++i){
		if ((que & (1 << i)) && indices.indexMap[i].has_value()) {
			vkGetDeviceQueue(dev, indices.indexMap[i].value(), index, &deviceQue.que);
			break;
		}
	}
	return deviceQue;
}

void LogicalDevice::waitForFences(const FenceGroup& group, VkBool32 waitAll, uint64_t timeout) {
	vkWaitForFences(dev, group.size(), group.data(), waitAll, timeout);
}

void LogicalDevice::waitForFence(const Fence& fence, VkBool32 waitAll, uint64_t timeout) {
	vkWaitForFences(dev, 1, fence.data(), waitAll, timeout);
}

void LogicalDevice::resetFences(const FenceGroup& group) {
	if (group.size() > 0) {
		vkResetFences(dev, group.size(), group.data());
	}
}

void LogicalDevice::waitIdle() {
	vkDeviceWaitIdle(dev);
}
