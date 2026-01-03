#include "DeviceMemory.h"

DeviceMemory::DeviceMemory() {

}

DeviceMemory::DeviceMemory(LogicalDevice d)
:dev(d){

}

void DeviceMemory::free() {
    vkFreeMemory(dev.value(), memory, nullptr);
}

void DeviceMemory::copyMemory(const void* vertexData, int deviceOffset, int deviceSize, VkMemoryMapFlags flags) {
    void* data;
    vkMapMemory(dev.value(), memory, deviceOffset, deviceSize, flags, &data);
    memcpy(data, vertexData, deviceSize);
    vkUnmapMemory(dev.value(), memory);
}