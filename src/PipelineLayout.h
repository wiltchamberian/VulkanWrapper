#pragma once
#include "export.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API PipelineLayout {
public:
	VkPipelineLayout& value() {
		return pipelineLayout;
	}
private:
	VkPipelineLayout pipelineLayout;
};