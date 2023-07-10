#pragma once
#include <string>
#include <vector>
#include "export.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API Shader {
public:
	friend class ShaderStageBuilder;
	Shader& clearSpecializations();
	Shader& addMapEntry(uint32_t constantID, uint32_t offset, size_t siz);
	Shader& popMapEntry();
	Shader& setConstantData(uint8_t* d, size_t siz);
	VkShaderModule getModule();
	VkPipelineShaderStageCreateFlags flags;
	std::string funcName;
	std::string name;
	//着色器类型（顶点，像素...)
	VkShaderStageFlagBits stage;
	std::vector<VkSpecializationMapEntry> mapEntries;
	std::vector<uint8_t> data;
private:
	VkShaderModule module;
	//Specialization,给着色其传递一些可实时修改的特化常量
	//layout(constant_id = 0) const vec4 SpecialColor = vec4(1.0, 0.0, 0.0, 1.0);
	
};