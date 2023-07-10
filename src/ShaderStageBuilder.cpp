#include "ShaderStageBuilder.h"
#include <stdexcept>

ShaderStageBuilder::ShaderStageBuilder(LogicalDevice d)
    :dev(d)
{
}

Shader ShaderStageBuilder::build() {
    VkShaderModule mod = createShaderModule(code);
    Shader shader;
    shader.name = name;
    shader.module = mod;
    shader.stage = stageFlags;
    shader.flags = pipelineStageCreateFlags;
    return shader;
}

ShaderStageBuilder& ShaderStageBuilder::setShaderName(const char* name) {
    this->name = std::string(name);
    return *this;
}

ShaderStageBuilder& ShaderStageBuilder::setShaderName(const std::string& name) {
    this->name = name;
    return *this;
}

ShaderStageBuilder& ShaderStageBuilder::setFuncName(const char* name) {
    this->funcName = name;
    return *this;
}

ShaderStageBuilder& ShaderStageBuilder::setFuncName(const std::string& name) {
    
    return *this;

}

ShaderStageBuilder& ShaderStageBuilder::setShaderCode(const std::vector<char>& code) {
    this->code = code;
    return *this;
}

ShaderStageBuilder& ShaderStageBuilder::setStageFlags(VkShaderStageFlagBits flags) {
    stageFlags = flags;
    return *this;
}

ShaderStageBuilder& ShaderStageBuilder::setPipelineCreateFlags(VkPipelineShaderStageCreateFlagBits flags) {
    pipelineStageCreateFlags = flags;
    return *this;
}

VkShaderModule ShaderStageBuilder::createShaderModule(const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(dev.dev, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}