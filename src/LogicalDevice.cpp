#include "LogicalDevice.h"
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
