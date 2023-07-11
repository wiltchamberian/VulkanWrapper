#pragma once

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API RenderPass {
public:
	void cleanUp();
	VkRenderPass& value() { return pass; }
private:
	LogicalDevice dev;
	VkRenderPass pass;
};