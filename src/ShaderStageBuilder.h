#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class ShaderStageBuilder {
public:
	void setDevice(LogicalDevice dev);
	VkShaderModule createShaderModule(const std::vector<char>& code);

private:
	LogicalDevice dev;
};