#ifndef __VMA_H
#define __VMA_H


#include "vk_mem_alloc.h"
#include "LogicalDevice.h"

class Buffer;

class VULKAN_WRAPPER_API Vma {
public:
    Vma(LogicalDevice dev);
    ~Vma();
    Vma& SetFlags(VmaAllocationCreateFlags flags);
    Vma& SetUsage(VmaMemoryUsage usage);
    Buffer CreateBuffer(VkBufferCreateInfo ci);
    void ReleaseBuffer(Buffer& buffer);
    void MapData(Buffer& buffer, const void* data, int siz);
protected:
    VmaAllocationCreateInfo ci;
    VmaAllocator allocator;
};

#endif