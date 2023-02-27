#pragma once

#include "Pipeline.h"
#include "LogicalDevice.h"
#include "RenderPass.h"

class VULKAN_WRAPPER_API PipelineBuilder {
public:
	VkShaderModule createShaderModule(const std::vector<char>& code);
	Pipeline build();

private:
	VkPipelineLayout layout;
	LogicalDevice dev;
	RenderPass renderPass;
};