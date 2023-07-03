#ifndef __DEVICE_QUEUE_H
#define __DEVICE_QUEUE_H

#include "export.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API DeviceQueue {
public:
	friend class LogicalDevice;
private:
	VkQueue que = VK_NULL_HANDLE;
};

#endif