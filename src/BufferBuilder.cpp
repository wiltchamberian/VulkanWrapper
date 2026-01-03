#include "BufferBuilder.h"
#include <stdexcept>


BufferBuilder::BufferBuilder() :ci{} {
    
}

BufferBuilder::BufferBuilder(LogicalDevice d)
:dev(d),
ci{} {

}

BufferBuilder& BufferBuilder::SetSize(int siz) {
    ci.size = siz;
    return *this;
}

BufferBuilder& BufferBuilder::SetFlags(VkBufferCreateFlagBits flags) {
    ci.flags = flags;
    return *this;
}

BufferBuilder& BufferBuilder::SetUsage(VkBufferUsageFlags usages) {
    ci.usage = usages;
    return *this;
}

BufferBuilder& BufferBuilder::SetSharingMode(VkSharingMode mode) {
    ci.sharingMode = mode;
    return *this;
}

Buffer BufferBuilder::build() {
    Buffer buffer(dev);
    if (vkCreateBuffer(dev.value(), &ci, nullptr, &buffer.value()) != VK_SUCCESS) {
         throw std::runtime_error("failed to create vertex buffer!");
    }
    return buffer;
}