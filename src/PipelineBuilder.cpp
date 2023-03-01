#include <stdexcept>
#include <fstream>
#include "PipelineBuilder.h"
#include "Tools.h"

VkShaderModule PipelineBuilder::createShaderModule(const std::vector<char>& code) {
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

Pipeline PipelineBuilder::build() {
    Pipeline pipeline;

    auto vertShaderCode = help::readFile(vertexPath.c_str());
    auto fragShaderCode = help::readFile(fragmentPath.c_str());

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(dev.dev, &pipelineLayoutInfo, nullptr, &layout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = layout;
    pipelineInfo.renderPass = renderPass.pass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(dev.dev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline.pipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(dev.dev, fragShaderModule, nullptr);
    vkDestroyShaderModule(dev.dev, vertShaderModule, nullptr);

}

void PipelineBuilder::setVertexShaderPath(const std::string& path) {
    vertexPath = path;
}

void PipelineBuilder::setFragmentShaderPath(const std::string& path) {
    fragmentPath = path;
}

void PipelineBuilder::setGeometryShaderPath(const std::string& path) {
    geometryPath = path;
}

void PipelineBuilder::setComputeShaderPath(const std::string& path) {
    computePath = path;
}

void PipelineBuilder::setVertexInputBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vec) {
    vertexInputBindingDescriptions = vec;
}

void PipelineBuilder::setVertexInputAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vec) {
    vertexInputAttributeDescriptions = vec;
}

void PipelineBuilder::setPrimitiveTopology(VkPrimitiveTopology topo) {
    topology = topo;
}

void PipelineBuilder::setAssemblyStateCreateFlags(VkPipelineInputAssemblyStateCreateFlags flags) {
    assemblyStateCreateFlags = flags;
}

void PipelineBuilder::setPrimitiveRestartEnable(VkBool32 enable) {
    primitiveRestartEnable = enable;
}

void PipelineBuilder::setViewportStateCreateFlags(VkPipelineViewportStateCreateFlags flags) {
    viewportStateCreateFlags = flags;
}

void PipelineBuilder::setViewports(const std::vector<VkViewport>& vps) {
    viewports = vps;
}

void PipelineBuilder::setScissors(const std::vector<VkRect2D>& vec) {
    scissors = vec;
}

void PipelineBuilder::setRasterizationStateCreateFlags(VkPipelineRasterizationStateCreateFlags flags) {
    rasterizationStateCreateInfoFlags = flags;
}

void PipelineBuilder::setDepthClampEnable(VkBool32 enable) {
    depthClampEnable = enable;
}

void PipelineBuilder::setRasterizerDiscardEnable(VkBool32 enable) {
    rasterizerDiscardEnable = enable;
}

void PipelineBuilder::setPolygonMode(VkPolygonMode mode) {
    polygonMode = mode;
}

void PipelineBuilder::setCullMode(VkCullModeFlags flags) {
    cullModeFlags = flags;
}

void PipelineBuilder::setFrontFace(VkFrontFace face) {
    frontFace = face;
}

void PipelineBuilder::setDepthBiasEnable(VkBool32 enable) {
    depthBiasEnable = enable;
}

void PipelineBuilder::setDepthBiasConstantFactor(float factor) {
    depthBiasConstantFactor = factor;
}

void PipelineBuilder::setDepthBiasClamp(float clamp) {
    depthBiasClamp = clamp;
}

void PipelineBuilder::setDepthBiasSlopeFactor(float slopFactor) {
    depthBiasSlopeFactor = slopFactor;
}

void PipelineBuilder::setLineWidth(float width) {
    lineWidth = width;
}

void PipelineBuilder::setMultisampleStateCreateFlags(VkPipelineMultisampleStateCreateFlags flags) {
    multiSampleStateCreateFlags = flags;
}

void PipelineBuilder::setSampleCountFlagBits(VkSampleCountFlagBits bits) {
    rasterizationSamples = bits;
}

void PipelineBuilder::setSampleShadingEnable(VkBool32 enable) {
    sampleShadingEnable = enable;
}

void PipelineBuilder::setMinSampleShading(float shading) {
    minSampleShading = shading;
}

void PipelineBuilder::setSampleMASK(const VkSampleMask* pMask) {
    pSampleMask = pMask;
}

void PipelineBuilder::setAlphaToCoverageEnable(VkBool32 enable) {
    alphaToCoverageEnable = enable;
}

void PipelineBuilder::setAlphaToOneEnable(VkBool32 enable) {
    alphaToOneEnable = enable;
}