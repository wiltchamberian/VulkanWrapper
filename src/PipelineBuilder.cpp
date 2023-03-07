#include <stdexcept>
#include <fstream>
#include "PipelineBuilder.h"
#include "Tools.h"

Pipeline PipelineBuilder::build() {
    Pipeline pipeline;

    std::vector< VkPipelineShaderStageCreateInfo> shaderStages;
    for (int i = 0; i < shaders.size(); ++i) {
        VkPipelineShaderStageCreateInfo ci;
        ci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ci.flags = shaders[i].flags;
        ci.stage = shaders[i].stage;
        ci.module = shaders[i].module;
        ci.pName = shaders[i].name.c_str();
        
        //TODO
        /*ci.pSpecializationInfo->pMapEntries = shaders[i].specializationInfo.mapEntries.data();
        ci.pSpecializationInfo->mapEntryCount = shaders[i].specializationInfo.mapEntries.size();
        ci.pSpecializationInfo->pData = shaders[i].specializationInfo.data;
        ci.pSpecializationInfo->dataSize = shaders[i].specializationInfo.dataSize;*/
    
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
    ci.renderPass = renderPass.pass;
    ci.subpass = 0;
    ci.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(dev.dev, VK_NULL_HANDLE, 1, &ci, nullptr, &pipeline.pipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

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

//void PipelineBuilder::setBlendEnable(VkBool32 enable) {
//    colorBlendAttachmentState.blendEnable = enable;
//}
//
//void PipelineBuilder::setSrcColorBlendFactor(VkBlendFactor factor) {
//    colorBlendAttachmentState.srcColorBlendFactor = factor;
//}
//
//void PipelineBuilder::setDstColorBlendFactor(VkBlendFactor factor) {
//    colorBlendAttachmentState.dstColorBlendFactor = factor;
//}
//
//void PipelineBuilder::setColorBlendOp(VkBlendOp op) {
//    colorBlendAttachmentState.colorBlendOp = op;
//}
//
//void PipelineBuilder::setSrcAlphaBlendFactor(VkBlendFactor factor) {
//    colorBlendAttachmentState.srcAlphaBlendFactor = factor;
//}
//
//void PipelineBuilder::setDstAlphaBlendFactor(VkBlendFactor factor) {
//    colorBlendAttachmentState.dstAlphaBlendFactor = factor;
//}
//
//void PipelineBuilder::setAlphaBlendOp(VkBlendOp op) {
//    colorBlendAttachmentState.alphaBlendOp = op;
//}
//
//void PipelineBuilder::setColorComponentFlags(VkColorComponentFlags colorWriteMask) {
//    colorBlendAttachmentState.colorWriteMask = colorWriteMask;
//}

void PipelineBuilder::setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState>& vec) {
    colorBlendAttachmentStates = vec;
}

void PipelineBuilder::setColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags flags) {
    colorBlendStateCreateflags = flags;
}

void PipelineBuilder::setColorBlendLogicOpEnable(VkBool32 enalbe) {
    colorBlendLogicOpEnable = enalbe;
}

void PipelineBuilder::setColorBlendLogicOp(VkLogicOp op) {
    colorBlendlogicOp = op;
}

void PipelineBuilder::setColorBlendConstants(float d[4]) {
    colorBlendConstants[0] = d[0];
    colorBlendConstants[1] = d[1];
    colorBlendConstants[2] = d[2];
    colorBlendConstants[3] = d[3];
}

void PipelineBuilder::setPipelineDynamicStateCreateFlags(VkPipelineDynamicStateCreateFlags flags) {
    dynamicStateCreateFlags = flags;
}

void PipelineBuilder::setDynamicStates(const std::vector<VkDynamicState>& vec) {
    dynamicStates = vec;
}

void PipelineBuilder::setPipelineLayout(const PipelineLayout& l) {
    pipelineLayout = l;
}