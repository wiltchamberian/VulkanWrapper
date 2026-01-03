#include "Buffer.h"
#include "DeviceMemory.h"

Buffer::Buffer() {


}

Buffer::Buffer(LogicalDevice d)
:dev(d){

}

void Buffer::cleanUp() {
    vkDestroyBuffer(dev.value(), buffer, nullptr);
}

VkMemoryRequirements Buffer::getMemoryRequirements() {
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(dev.value(), buffer, &memRequirements);
    return memRequirements;
}

void Buffer::bindMemory(DeviceMemory memory, int offset) {
    vkBindBufferMemory(dev.value(), buffer, memory.value(), offset);
}