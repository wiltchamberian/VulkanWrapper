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
	//��ɫ�����ͣ����㣬����...)
	VkShaderStageFlagBits stage;
	std::vector<VkSpecializationMapEntry> mapEntries;
	std::vector<uint8_t> data;
private:
	VkShaderModule module;
	//Specialization,����ɫ�䴫��һЩ��ʵʱ�޸ĵ��ػ�����
	//layout(constant_id = 0) const vec4 SpecialColor = vec4(1.0, 0.0, 0.0, 1.0);
	
};