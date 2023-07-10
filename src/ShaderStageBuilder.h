#pragma once
#include <vector>
#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"
#include "Shader.h"

class VULKAN_WRAPPER_API ShaderStageBuilder {
public:
	ShaderStageBuilder(LogicalDevice dev);
	Shader build();
	ShaderStageBuilder& setShaderName(const char* name);
	ShaderStageBuilder& setShaderName(const std::string& name);
	ShaderStageBuilder& setFuncName(const char* name);
	ShaderStageBuilder& setFuncName(const std::string& name);
	ShaderStageBuilder& setShaderCode(const std::vector<char>& code);
	ShaderStageBuilder& setStageFlags(VkShaderStageFlagBits flags);
	ShaderStageBuilder& setPipelineCreateFlags(VkPipelineShaderStageCreateFlagBits flags);
private:
	VkShaderModule createShaderModule(const std::vector<char>& code);
	LogicalDevice dev;
	std::string name;
	std::string funcName;
	std::vector<char> code;
	VkShaderStageFlagBits stageFlags;
	VkPipelineShaderStageCreateFlagBits pipelineStageCreateFlags;
};