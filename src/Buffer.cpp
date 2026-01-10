#include "Buffer.h"
#include "DeviceMemory.h"
#include <stdexcept>

Buffer::Buffer() {


}

Buffer::Buffer(LogicalDevice d)
:dev(d){

}

void Buffer::cleanUp() {
    if (!allocatedByVma) {
        vkDestroyBuffer(dev.value(), buffer, nullptr);
    }
}

VkMemoryRequirements Buffer::getMemoryRequirements() {
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(dev.value(), buffer, &memRequirements);
    return memRequirements;
}

void Buffer::bindMemory(DeviceMemory memory, int offset) {
    VkResult result = vkBindBufferMemory(dev.value(), buffer, memory.value(), offset);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("buffer failed to bind memory!");
    }
    else {
        this->offset = offset;
        this->memory = memory;
    }
}

void Buffer::copyData(const void* vertexData, int deviceSize, VkMemoryMapFlags flags) {
    void* data;
    vkMapMemory(dev.value(), memory.value(), offset, deviceSize, flags, &data);
    memcpy(data, vertexData, deviceSize);
    vkUnmapMemory(dev.value(), memory.value());
}