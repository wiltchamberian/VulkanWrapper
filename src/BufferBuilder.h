#ifndef __BUFFER_BUILDER_H
#define __BUFFER_BUILDER_H

#include "Buffer.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API BufferBuilder {
public:
    BufferBuilder();
    BufferBuilder(LogicalDevice dev);
    BufferBuilder& SetSize(int siz);
    BufferBuilder& SetFlags(VkBufferCreateFlagBits);
    BufferBuilder& SetUsage(VkBufferUsageFlags usages);
    BufferBuilder& SetSharingMode(VkSharingMode mode);
    Buffer build();

private:
    LogicalDevice dev;
    VkBufferCreateInfo ci;
};

#endif