#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"


class VULKAN_WRAPPER_API PipelineLayout {
public:
	VkPipelineLayout& value() {
		return pipelineLayout;
	}
	void cleanUp();
private:
	LogicalDevice dev;
	VkPipelineLayout pipelineLayout;
};