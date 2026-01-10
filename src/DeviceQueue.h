#ifndef __DEVICE_QUEUE_H
#define __DEVICE_QUEUE_H

#include "export.h"
#include "vulkan/vulkan.h"

class Fence;

class VULKAN_WRAPPER_API DeviceQueue {
public:
	friend class LogicalDevice;
	void submit(const VkSubmitInfo& submitInfo, const Fence& fence);
	VkResult presentKHR(const VkPresentInfoKHR& presentInfo);
	void waitIdle();
private:
	VkQueue que = VK_NULL_HANDLE;
};

#endif