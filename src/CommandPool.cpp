#include "CommandPool.h"
#include "CommandBuffer.h"
#include <stdexcept>

void CommandPool::cleanUp() {
	if (dev.isValid()) {
		vkDestroyCommandPool(dev.value(), pool, nullptr);
	}
}

CommandBuffer CommandPool::allocBuffer(VkCommandBufferLevel level) {
	CommandBuffer buffer;
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = this->pool;
	allocInfo.level = level;
	allocInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(dev.value(), &allocInfo, &buffer.buf) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	else {
	}
	return buffer;
}

std::vector<CommandBuffer> CommandPool::allocBuffers(VkCommandBufferLevel level, uint32_t count) {
	if (count <= 0) return {};
	std::vector<CommandBuffer> buffers;
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = this->pool;
	allocInfo.level = level;
	allocInfo.commandBufferCount = count;
	std::vector<VkCommandBuffer> bufs(count);
	if (vkAllocateCommandBuffers(dev.value(), &allocInfo, bufs.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	else {
		buffers.resize(count);
		for (int i = 0; i < count; ++i) {
			buffers[i].buf = bufs[i];
		}
	}
	return buffers;
}

void CommandPool::destroyBuffer(const CommandBuffer& buf) {

}