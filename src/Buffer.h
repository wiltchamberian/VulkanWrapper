#ifndef __BUFFER_H
#define __BUFFER_H

#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class DeviceMemory;

class VULKAN_WRAPPER_API Buffer {
public:
    Buffer();
    Buffer(LogicalDevice dev);
    VkBuffer& value() { return buffer; }
    void cleanUp();
    VkMemoryRequirements getMemoryRequirements();
    void bindMemory(DeviceMemory memory, int offset);
private:
    LogicalDevice dev;
    VkBuffer buffer = VK_NULL_HANDLE;
};

#endif