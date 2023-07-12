#include "CommandBuffer.h"
#include <stdexcept>

CommandBuffer& CommandBuffer::begin(VkCommandBufferBeginInfo info) {
	if (vkBeginCommandBuffer(buf, &info) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	return *this;
}

CommandBuffer& CommandBuffer::end() {
	if (vkEndCommandBuffer(buf) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
	return *this;
}