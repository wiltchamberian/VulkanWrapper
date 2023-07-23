#include "CommandBuffer.h"
#include <stdexcept>

CommandBuffer& CommandBuffer::begin(VkCommandBufferBeginInfo info) {
	if (vkBeginCommandBuffer(buf, &info) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	return *this;
}

CommandBuffer& CommandBuffer::begin(VkCommandBufferUsageFlags flags, const VkCommandBufferInheritanceInfo* pInheritanceInfo) {
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = flags;
	beginInfo.pInheritanceInfo = pInheritanceInfo;
	if (vkBeginCommandBuffer(buf, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	return *this;

}

CommandBuffer& CommandBuffer::beginRenderPass(VkRenderPassBeginInfo info, VkSubpassContents content) {
	vkCmdBeginRenderPass(buf, &info, content);
	return *this;
}

CommandBuffer& CommandBuffer::bindPipeline(Pipeline& pipeline, VkPipelineBindPoint bindPoint) {
	vkCmdBindPipeline(buf, bindPoint, pipeline.value());
	return *this;
}

CommandBuffer& CommandBuffer::setViewPort(uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports){
	vkCmdSetViewport(buf, firstViewport, viewportCount, pViewports);
	return *this;
}

CommandBuffer& CommandBuffer::setViewPort(VkViewport& pViewport) {
	vkCmdSetViewport(buf, 0, 1, &pViewport);
	return *this;
}

CommandBuffer& CommandBuffer::setScissor(uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
	vkCmdSetScissor(buf, firstScissor, scissorCount, pScissors);
	return *this;
}

CommandBuffer& CommandBuffer::setScissor(VkRect2D& pScissor) {
	vkCmdSetScissor(buf, 0, 1, &pScissor);
	return *this;
}

CommandBuffer& CommandBuffer::draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
	vkCmdDraw(buf, vertexCount, instanceCount, firstVertex, firstInstance);
	return *this;
}

CommandBuffer& CommandBuffer::endRenderPass() {
	vkCmdEndRenderPass(buf);
	return *this;
}

CommandBuffer& CommandBuffer::end() {
	if (vkEndCommandBuffer(buf) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
	return *this;
}

CommandBuffer& CommandBuffer::reset(VkCommandBufferResetFlags flags) {
	vkResetCommandBuffer(buf, flags);
	return *this;
}

CommandBuffer& CommandBuffer::record() {
	return *this;
}