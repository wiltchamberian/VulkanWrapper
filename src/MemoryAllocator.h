#ifndef __MEMORY_ALLOCATOR_H
#define __MEMORY_ALLOCATOR_H

#include "export.h"
#include "DeviceMemory.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API MemoryAllocator {
public:
    MemoryAllocator(LogicalDevice dev);
    DeviceMemory allocateMemory();
    MemoryAllocator& SetAllocationSize(uint64_t siz);
    MemoryAllocator& SetMemoryTypeIndex(uint32_t index);
private:
    LogicalDevice dev;
    VkMemoryAllocateInfo ai = {};
};






#endif