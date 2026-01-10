#pragma once

#include "export.h"
#include "LogicalDevice.h"


class VULKAN_WRAPPER_API Pipeline {
public:
	friend class PipelineBuilder;
	VkPipeline& value();
	void cleanUp();
private:
	LogicalDevice dev;
	VkPipeline pipeline = VK_NULL_HANDLE;
};

