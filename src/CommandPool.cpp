#include "CommandPool.h"
#include "CommandBuffer.h"
#include <stdexcept>

void CommandPool::cleanUp() {
	if (dev.isValid()) {
		vkDestroyCommandPool(dev.dev, pool, nullptr);
	}
}

CommandBuffer CommandPool::allocBuffer(VkCommandBufferLevel level, uint32_t count) {
	CommandBuffer buffer;
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = this->pool;
	allocInfo.level = level;
	allocInfo.commandBufferCount = count;
	if (vkAllocateCommandBuffers(dev.dev, &allocInfo, &buffer.buf) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	return buffer;
}

void CommandPool::destroyBuffer(const CommandBuffer& buf) {
	
}