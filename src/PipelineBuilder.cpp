#include <stdexcept>
#include <fstream>
#include "PipelineBuilder.h"
#include "Tools.h"

PipelineBuilder::PipelineBuilder(const LogicalDevice& d)
:depthBiasConstantFactor(0.0)
,depthBiasClamp(0.0)
,depthBiasSlopeFactor(0.0)
,lineWidth(0.0)
,dev(d)
{

}

Pipeline PipelineBuilder::build() {
    Pipeline pipeline;

    std::vector< VkPipelineShaderStageCreateInfo> shaderStages;
    std::vector<VkSpecializationInfo> specilizations(shaders.size());
    for (int i = 0; i < shaders.size(); ++i) {
        VkPipelineShaderStageCreateInfo ci;
        ci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ci.flags = shaders[i].flags;
        ci.stage = shaders[i].stage;
        ci.module = shaders[i].getModule();
        ci.pName = shaders[i].funcName.c_str();

        //why vulkan use a pointer type of specializationInfo?
        specilizations[i].pMapEntries = shaders[i].mapEntries.data();
        specilizations[i].mapEntryCount = shaders[i].mapEntries.size();
        specilizations[i].pData = shaders[i].data.data();
        specilizations[i].dataSize = shaders[i].data.size();
        ci.pSpecializationInfo = &specilizations[i];

        shaderStages.push_back(ci);
    }

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = vertexInputBindingDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = vertexInputBindingDescriptions.data();
    vertexInputInfo.vertexAttributeDescriptionCount = vertexInputAttributeDescriptions.size();
    vertexInputInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = topology;
    inputAssembly.primitiveRestartEnable = primitiveRestartEnable;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.flags = viewportStateCreateFlags;
    viewportState.viewportCount = viewports.size();
    viewportState.pViewports = viewports.data();
    viewportState.pScissors = scissors.data();
    viewportState.scissorCount = scissors.size();

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.flags = rasterizationStateCreateInfoFlags;
    rasterizer.depthClampEnable = depthClampEnable;
    rasterizer.rasterizerDiscardEnable = rasterizerDiscardEnable;
    rasterizer.polygonMode = polygonMode;
    rasterizer.lineWidth = lineWidth;
    rasterizer.cullMode = cullModeFlags;
    rasterizer.frontFace = frontFace;
    rasterizer.depthBiasEnable = depthBiasEnable;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.flags = multiSampleStateCreateFlags;
    multisampling.sampleShadingEnable = sampleShadingEnable;
    multisampling.rasterizationSamples = rasterizationSamples;
    multisampling.minSampleShading = minSampleShading;
    multisampling.alphaToCoverageEnable = alphaToCoverageEnable;
    multisampling.alphaToOneEnable = alphaToOneEnable;
    multisampling.pSampleMask = pSampleMask;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = colorBlendLogicOpEnable;
    colorBlending.logicOp = colorBlendlogicOp;
    colorBlending.attachmentCount = colorBlendAttachmentStates.size();
    colorBlending.pAttachments = colorBlendAttachmentStates.data();
    colorBlending.blendConstants[0] = colorBlendConstants[0];
    colorBlending.blendConstants[1] = colorBlendConstants[1];
    colorBlending.blendConstants[2] = colorBlendConstants[2];
    colorBlending.blendConstants[3] = colorBlendConstants[3];

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    VkGraphicsPipelineCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    ci.stageCount = shaderStages.size();
    ci.pStages = shaderStages.data();
    ci.pVertexInputState = &vertexInputInfo;
    ci.pInputAssemblyState = &inputAssembly;
    ci.pViewportState = &viewportState;
    ci.pRasterizationState = &rasterizer;
    ci.pMultisampleState = &multisampling;
    ci.pColorBlendState = &colorBlending;
    ci.pDynamicState = &dynamicState;
    ci.layout = pipelineLayout.value();
    ci.renderPass = renderPass.value();
    ci.subpass = subpass;
    ci.basePipelineHandle = basePipeline.value();
    ci.basePipelineIndex = basePipelineIndex;

    if (vkCreateGraphicsPipelines(dev.value(), VK_NULL_HANDLE, 1, &ci, nullptr, &pipeline.pipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }
    else {
        pipeline.dev = this->dev;
    }

    return pipeline;
}

PipelineBuilder& PipelineBuilder::setShaders(const std::vector<Shader>& vec) {
    shaders = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setVertexInputBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vec) {
    vertexInputBindingDescriptions = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setVertexInputAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vec) {
    vertexInputAttributeDescriptions = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPrimitiveTopology(VkPrimitiveTopology topo) {
    topology = topo;
    return *this;
}

PipelineBuilder& PipelineBuilder::setAssemblyStateCreateFlags(VkPipelineInputAssemblyStateCreateFlags flags) {
    assemblyStateCreateFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPrimitiveRestartEnable(VkBool32 enable) {
    primitiveRestartEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setViewportStateCreateFlags(VkPipelineViewportStateCreateFlags flags) {
    viewportStateCreateFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setViewports(const std::vector<VkViewport>& vps) {
    viewports = vps;
    return *this;
}

PipelineBuilder& PipelineBuilder::setScissors(const std::vector<VkRect2D>& vec) {
    scissors = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRasterizationStateCreateFlags(VkPipelineRasterizationStateCreateFlags flags) {
    rasterizationStateCreateInfoFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthClampEnable(VkBool32 enable) {
    depthClampEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRasterizerDiscardEnable(VkBool32 enable) {
    rasterizerDiscardEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPolygonMode(VkPolygonMode mode) {
    polygonMode = mode;
    return *this;
}

PipelineBuilder& PipelineBuilder::setCullMode(VkCullModeFlags flags) {
    cullModeFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setFrontFace(VkFrontFace face) {
    frontFace = face;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthBiasEnable(VkBool32 enable) {
    depthBiasEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthBiasConstantFactor(float factor) {
    depthBiasConstantFactor = factor;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthBiasClamp(float clamp) {
    depthBiasClamp = clamp;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDepthBiasSlopeFactor(float slopFactor) {
    depthBiasSlopeFactor = slopFactor;
    return *this;
}

PipelineBuilder& PipelineBuilder::setLineWidth(float width) {
    lineWidth = width;
    return *this;
}

PipelineBuilder& PipelineBuilder::setMultisampleStateCreateFlags(VkPipelineMultisampleStateCreateFlags flags) {
    multiSampleStateCreateFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRasterizationSamples(VkSampleCountFlagBits bits) {
    rasterizationSamples = bits;
    return *this;
}

PipelineBuilder& PipelineBuilder::setSampleShadingEnable(VkBool32 enable) {
    sampleShadingEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setMinSampleShading(float shading) {
    minSampleShading = shading;
    return *this;
}

PipelineBuilder& PipelineBuilder::setSampleMask(const VkSampleMask* pMask) {
    pSampleMask = pMask;
    return *this;
}

PipelineBuilder& PipelineBuilder::setAlphaToCoverageEnable(VkBool32 enable) {
    alphaToCoverageEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setAlphaToOneEnable(VkBool32 enable) {
    alphaToOneEnable = enable;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState>& vec) {
    colorBlendAttachmentStates = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags flags) {
    colorBlendStateCreateflags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendLogicOpEnable(VkBool32 enalbe) {
    colorBlendLogicOpEnable = enalbe;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendLogicOp(VkLogicOp op) {
    colorBlendlogicOp = op;
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendConstants(float d[4]) {
    colorBlendConstants[0] = d[0];
    colorBlendConstants[1] = d[1];
    colorBlendConstants[2] = d[2];
    colorBlendConstants[3] = d[3];
    return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendConstants(float d0, float d1, float d2, float d3) {
    colorBlendConstants[0] = d0;
    colorBlendConstants[1] = d1;
    colorBlendConstants[2] = d2;
    colorBlendConstants[3] = d3;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPipelineDynamicStateCreateFlags(VkPipelineDynamicStateCreateFlags flags) {
    dynamicStateCreateFlags = flags;
    return *this;
}

PipelineBuilder& PipelineBuilder::setDynamicStates(const std::vector<VkDynamicState>& vec) {
    dynamicStates = vec;
    return *this;
}

PipelineBuilder& PipelineBuilder::setPipelineLayout(const PipelineLayout& l) {
    pipelineLayout = l;
    return *this;
}

PipelineBuilder& PipelineBuilder::setRenderPass(RenderPass pass) {
    renderPass = pass;
    return *this;
}

PipelineBuilder& PipelineBuilder::setSubPass(uint32_t id) {
    subpass = id;
    return *this;
}

PipelineBuilder& PipelineBuilder::setBasePipelineHandle(Pipeline pipeline) {
    basePipeline = pipeline;
    return *this;
}

PipelineBuilder& PipelineBuilder::setBasePipelineIndex(int32_t index) {
    basePipelineIndex = index;
    return *this;
}