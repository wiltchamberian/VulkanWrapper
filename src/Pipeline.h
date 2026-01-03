#pragma once
#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API Pipeline {
public:
	friend class PipelineBuilder;
	VkPipeline& value() { return pipeline; }
	void cleanUp();
	void Test();
private:
	LogicalDevice dev;
	VkPipeline pipeline = VK_NULL_HANDLE;
};

