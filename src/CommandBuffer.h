#ifndef __COMMAND_BUFFER_H
#define __COMMAND_BUFFER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "Pipeline.h"

class CommandBuffer {
public:
	friend class CommandPool;
	CommandBuffer& begin(VkCommandBufferBeginInfo info);
	CommandBuffer& begin(VkCommandBufferUsageFlags flags, const VkCommandBufferInheritanceInfo* pInheritanceInfo = nullptr);
	CommandBuffer& beginRenderPass(VkRenderPassBeginInfo info, VkSubpassContents content);
	CommandBuffer& bindPipeline(Pipeline& pipeline, VkPipelineBindPoint bindPoint);
	CommandBuffer& setViewPort(uint32_t firstViewport,uint32_t viewportCount,const VkViewport* pViewports);
	CommandBuffer& setViewPort(VkViewport& pViewport);
	CommandBuffer& setScissor(uint32_t firstScissor,uint32_t scissorCount,const VkRect2D* pScissors);
	CommandBuffer& setScissor(VkRect2D& pScissor);
	CommandBuffer& draw(uint32_t vertexCount,uint32_t instanceCount,uint32_t firstVertex,uint32_t firstInstance);
	CommandBuffer& endRenderPass();
	CommandBuffer& end();
	CommandBuffer& reset(VkCommandBufferResetFlags flags = 0);
	CommandBuffer& record();
private:
	VkCommandBuffer buf = VK_NULL_HANDLE;
};




#endif