#pragma once
#include <string>
#include <vector>
#include "vulkan/vulkan.h"

struct SpecializationInfo {
	std::vector<VkSpecializationMapEntry> mapEntries;
	const void* data;
	size_t dataSize;
};

class Shader {
public:
	VkPipelineShaderStageCreateFlagBits flags;
	std::string name;
	VkShaderModule module;
	VkShaderStageFlagBits stage;
	SpecializationInfo specializationInfo;
};