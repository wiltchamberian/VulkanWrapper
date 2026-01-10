#include "Vma.h"
#include "Buffer.h"
#include <stdexcept>

#define VMA_IMPLEMENTATION 
#include "vk_mem_alloc.h"

Vma::Vma(LogicalDevice dev)
:ci{} 
{
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_2;

    allocatorInfo.physicalDevice = dev.physical_device().value();
    allocatorInfo.device = dev.value();
    allocatorInfo.instance = dev.physical_device().Instance().value();

    VkResult result = vmaCreateAllocator(&allocatorInfo, &allocator);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("vma allocate memory fail!");
    }
    else {
        return;
    }

}

Vma::~Vma() {
    if (allocator != VK_NULL_HANDLE) {
        vmaDestroyAllocator(allocator);
    }
}

Vma& Vma::SetFlags(VmaAllocationCreateFlags flags) {
    ci.flags = flags;

    return *this;
}

Vma& Vma::SetUsage(VmaMemoryUsage usage) {
    ci.usage = usage;
    return *this;
}

Buffer Vma::CreateBuffer(VkBufferCreateInfo b) {
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = ci.usage;
    allocInfo.flags = ci.flags;

    Buffer buffer;
    VkResult result = vmaCreateBuffer(allocator, &b, &allocInfo, &buffer.value(), &buffer.vmaAllocation(), nullptr);
    if (result != VK_SUCCESS) {
        buffer.value() = VK_NULL_HANDLE;
        throw std::runtime_error("vma create buffer failed!");
    }
    else {
        buffer.allocatedByVma = true;
    }
    return buffer;
}

void Vma::ReleaseBuffer(Buffer& buffer) {
    vmaDestroyBuffer(allocator, buffer.value(), buffer.vmaAllocation());
}

void Vma::MapData(Buffer& buffer, const void* data, int siz) {
    void* mapped = nullptr;
    vmaMapMemory(allocator, buffer.allocation, &mapped);

    memcpy(mapped,
        data,
        siz);

    vmaUnmapMemory(allocator, buffer.allocation);
}

