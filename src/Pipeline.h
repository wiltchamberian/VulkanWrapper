#pragma once
#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API Pipeline {
public:
	friend class PipelineBuilder;
	void cleanUp();
private:
	LogicalDevice dev;
	VkPipeline pipeline;
};

