#pragma once

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API RenderPass {
public:
	friend class RenderPassBuilder;
	void cleanUp();
	VkRenderPass& value() { return pass; }
private:
	LogicalDevice dev;
	VkRenderPass pass;
};