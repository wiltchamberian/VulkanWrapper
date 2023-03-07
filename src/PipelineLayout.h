#pragma once
#include "vulkan/vulkan.h"

class PipelineLayout {
public:
	VkPipelineLayout& value() {
		return pipelineLayout;
	}
private:
	VkPipelineLayout pipelineLayout;
};