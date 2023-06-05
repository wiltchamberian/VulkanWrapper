#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"
#include "Shader.h"

class ShaderStageBuilder {
public:
	ShaderStageBuilder& setDevice(LogicalDevice dev);
	Shader build();
	ShaderStageBuilder& setShaderName(const char* name);
	ShaderStageBuilder& setShaderName(const std::string& name);
	ShaderStageBuilder& setShaderCode(const std::vector<char>& code);
	ShaderStageBuilder& setStageFlags(VkShaderStageFlagBits flags);
	ShaderStageBuilder& setPipelineCreateFlags(VkPipelineShaderStageCreateFlagBits flags);
private:
	VkShaderModule createShaderModule(const std::vector<char>& code);
	LogicalDevice dev;
	std::string name;
	std::vector<char> code;
	VkShaderStageFlagBits stageFlags;
	VkPipelineShaderStageCreateFlagBits pipelineStageCreateFlags;
};