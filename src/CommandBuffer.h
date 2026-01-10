#ifndef __COMMAND_BUFFER_H
#define __COMMAND_BUFFER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Pipeline.h"
#include "Buffer.h"

class VULKAN_WRAPPER_API CommandBuffer {
public:
	friend class CommandPool;
	VkCommandBuffer& value() {
		return buf;
	}
	CommandBuffer& begin(const VkCommandBufferBeginInfo& info);
	CommandBuffer& begin(VkCommandBufferUsageFlags flags, const VkCommandBufferInheritanceInfo* pInheritanceInfo = nullptr);
	CommandBuffer& beginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content);
	CommandBuffer& bindPipeline(Pipeline& pipeline, VkPipelineBindPoint bindPoint);
	CommandBuffer& bindVertexBuffer(Buffer buffer, int deviceOffset);
	CommandBuffer& setViewPort(uint32_t firstViewport,uint32_t viewportCount,const VkViewport* pViewports);
	CommandBuffer& setViewPort(VkViewport& pViewport);
	CommandBuffer& setScissor(uint32_t firstScissor,uint32_t scissorCount,const VkRect2D* pScissors);
	CommandBuffer& setScissor(VkRect2D& pScissor);
	CommandBuffer& draw(uint32_t vertexCount,uint32_t instanceCount,uint32_t firstVertex,uint32_t firstInstance);
	CommandBuffer& endRenderPass();
	CommandBuffer& end();
	CommandBuffer& reset(VkCommandBufferResetFlags flags = 0);
	CommandBuffer& record();
	CommandBuffer& copyBuffer(VkBufferCopy region, Buffer srcBuffer, Buffer dstBuffer);
private:
	VkCommandBuffer buf = VK_NULL_HANDLE;
};




#endif