#ifndef __VULKAN_INSTANCE_H
#define __VULKAN_INSTANCE_H

#include "export.h"
#include "vulkan/vulkan.h"

typedef bool (*PhysicalDeviceFilter)(VkPhysicalDeviceProperties& properties, VkPhysicalDeviceFeatures& features);

class PhysicalDevice;
class Surface;

class VULKAN_WRAPPER_API VulkanInstance {
public:
	bool isValid() {
		return vk != VK_NULL_HANDLE;
	}
	VkInstance& value() {
		return vk;
	}
	PhysicalDevice selectPhysicalDevice(VkQueueFlags flags, Surface surface, PhysicalDeviceFilter filter = nullptr);
	void clearUp();
private:
	PhysicalDeviceFilter filter = nullptr;
	VkInstance vk = VK_NULL_HANDLE;
};

#endif