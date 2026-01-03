#ifndef __DEVICE_MEMORY_H
#define __DEVICE_MEMORY_H

#include "export.h"
#include "vulkan/vulkan.h"

#include "LogicalDevice.h"

class VULKAN_WRAPPER_API DeviceMemory {
public:
    DeviceMemory();
    DeviceMemory(LogicalDevice dev);
    VkDeviceMemory& value() { return memory; }
    void free();
    void copyMemory(const void* data, int deviceOffset, int deviceSize, VkMemoryMapFlags flags);
private:
    LogicalDevice dev;
    VkDeviceMemory memory = VK_NULL_HANDLE;
};


#endif