#ifndef __BUFFER_H
#define __BUFFER_H

#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"
#include "DeviceMemory.h"
#include "Vma.h"

class DeviceMemory;

class VULKAN_WRAPPER_API Buffer {
public:
    friend class Vma;
    Buffer();
    Buffer(LogicalDevice dev);
    VkBuffer& value() { return buffer; }
    void cleanUp();
    VkMemoryRequirements getMemoryRequirements();
    void bindMemory(DeviceMemory memory, int offset);
    void copyData(const void* vertexData, int deviceSize, VkMemoryMapFlags flags);
    VmaAllocation& vmaAllocation() { return allocation; }
    bool isAllocatedByVma() const {
        return allocatedByVma;
    }
private:
    int offset = -1;
    DeviceMemory memory;
    LogicalDevice dev;
    bool allocatedByVma = false;
    VkBuffer buffer = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;
};

#endif