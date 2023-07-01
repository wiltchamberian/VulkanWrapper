//This file is called baby as the visual studio has 
//a bug that if it is called PipelineBuilder, the 
//compiled lib can't find symbol....
#pragma once 

#include "export.h"
#include "Pipeline.h"
#include "Shader.h"
#include "PipelineLayout.h"
#include "LogicalDevice.h"
#include "RenderPass.h"
#include <string>


class VULKAN_WRAPPER_API PipelineBuilder {
public:
	Pipeline build();
	PipelineBuilder& setShaders(const std::vector<Shader>& shaders);

	//VkPipelineVertexInputStateCreateInfo
	PipelineBuilder& setVertexInputBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vec);
	PipelineBuilder& setVertexInputAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vec);

	//VkPipelineInputAssemblyStateCreateInfo
	PipelineBuilder& setPrimitiveTopology(VkPrimitiveTopology topology);
	PipelineBuilder& setAssemblyStateCreateFlags(VkPipelineInputAssemblyStateCreateFlags flags);
	PipelineBuilder& setPrimitiveRestartEnable(VkBool32 enable);

	//VkPipelineViewportStateCreateInfo
	PipelineBuilder& setViewportStateCreateFlags(VkPipelineViewportStateCreateFlags flags);
	PipelineBuilder& setViewports(const std::vector<VkViewport>& viewports);
	PipelineBuilder& setScissors(const std::vector<VkRect2D>& scirros);

	//VkPipelineRasterizationStateCreateInfo
	PipelineBuilder& setRasterizationStateCreateFlags(VkPipelineRasterizationStateCreateFlags flags);
	PipelineBuilder& setDepthClampEnable(VkBool32 enable);
	PipelineBuilder& setRasterizerDiscardEnable(VkBool32 enalbe);
	PipelineBuilder& setPolygonMode(VkPolygonMode mode);
	PipelineBuilder& setCullMode(VkCullModeFlags flags);
	PipelineBuilder& setFrontFace(VkFrontFace face);
	PipelineBuilder& setDepthBiasEnable(VkBool32 enable);
	PipelineBuilder& setDepthBiasConstantFactor(float factor);
	PipelineBuilder& setDepthBiasClamp(float factor);
	PipelineBuilder& setDepthBiasSlopeFactor(float slopFactor);
	PipelineBuilder& setLineWidth(float lineWidth);

	//VkPipelineMultisampleStateCreateInfo
	PipelineBuilder& setMultisampleStateCreateFlags(VkPipelineMultisampleStateCreateFlags flags);
	PipelineBuilder& setSampleCountFlagBits(VkSampleCountFlagBits rasterizationSamples);
	PipelineBuilder& setSampleShadingEnable(VkBool32 sampleShadingEnable);
	PipelineBuilder& setMinSampleShading(float minSampleShading);
	PipelineBuilder& setSampleMASK(const VkSampleMask* pSampleMask);
	PipelineBuilder& setAlphaToCoverageEnable(VkBool32 enable);
	PipelineBuilder& setAlphaToOneEnable(VkBool32 enable);

	//VkPipelineColorBlendCreateInfo
	PipelineBuilder& setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState>& vec);
	PipelineBuilder& setColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags flags);
	PipelineBuilder& setColorBlendLogicOpEnable(VkBool32 enalbe);
	PipelineBuilder& setColorBlendLogicOp(VkLogicOp op);
	PipelineBuilder& setColorBlendConstants(float d[4]);
	//void setBlendEnable(VkBool32 enable);
	//void setSrcColorBlendFactor(VkBlendFactor factor);
	//void setDstColorBlendFactor(VkBlendFactor factor);
	//void setColorBlendOp(VkBlendOp op);
	//void setSrcAlphaBlendFactor(VkBlendFactor factor);
	//void setDstAlphaBlendFactor(VkBlendFactor factor);
	//void setAlphaBlendOp(VkBlendOp op);
	//void setColorComponentFlags(VkColorComponentFlags colorWriteMask);

	//VkPipelineDynamicStateCreateInfo
	PipelineBuilder& setPipelineDynamicStateCreateFlags(VkPipelineDynamicStateCreateFlags flags);
	PipelineBuilder& setDynamicStates(const std::vector<VkDynamicState>& dynamicStates);

	//VkPipelineLayout
	PipelineBuilder& setPipelineLayout(const PipelineLayout& pipelineLayout);

	PipelineBuilder& setRenderPass(RenderPass pass);
	PipelineBuilder& setSubPass(uint32_t id);
private:
	PipelineLayout pipelineLayout;
	LogicalDevice dev;
	RenderPass renderPass;
	uint32_t subpass = 0;

	//VkPipelineShaderStageCreateInfo
	std::vector<Shader> shaders;

	//VkPipelineVertexInputStateCreateInfo
	std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;

	//VkPipelineInputAssemblyStateCreateInfo
	VkPipelineInputAssemblyStateCreateFlags assemblyStateCreateFlags;
	VkPrimitiveTopology topology;
	VkBool32  primitiveRestartEnable;

	//VkPipelineViewportStateCreateInfo
	VkPipelineViewportStateCreateFlags    viewportStateCreateFlags;
	std::vector<VkViewport>				  viewports;
	std::vector<VkRect2D>				  scissors;

	//VkPipelineRasterizationStateCreateInfo
	VkPipelineRasterizationStateCreateFlags    rasterizationStateCreateInfoFlags;
	VkBool32                                   depthClampEnable;
	VkBool32                                   rasterizerDiscardEnable;
	VkPolygonMode                              polygonMode;
	VkCullModeFlags                            cullModeFlags;
	VkFrontFace                                frontFace;
	VkBool32                                   depthBiasEnable;
	float                                      depthBiasConstantFactor;
	float                                      depthBiasClamp;
	float                                      depthBiasSlopeFactor;
	float                                      lineWidth;

	//VkPipelineMultisampleStateCreateInfo
	VkPipelineMultisampleStateCreateFlags    multiSampleStateCreateFlags;
	VkSampleCountFlagBits                    rasterizationSamples;
	VkBool32                                 sampleShadingEnable;
	float                                    minSampleShading;
	const VkSampleMask* pSampleMask;
	VkBool32                                 alphaToCoverageEnable;
	VkBool32                                 alphaToOneEnable;

	std::vector<VkPipelineColorBlendAttachmentState>    colorBlendAttachmentStates;
	VkPipelineColorBlendStateCreateFlags				colorBlendStateCreateflags;
	VkBool32											colorBlendLogicOpEnable;
	VkLogicOp											colorBlendlogicOp;
	float                                               colorBlendConstants[4];

	//VkPipelineDynamicStateCreateInfo
	VkPipelineDynamicStateCreateFlags					dynamicStateCreateFlags;
	std::vector<VkDynamicState>							dynamicStates;
};