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
#include "vulkan/vulkan.h"
#include <string>


class VULKAN_WRAPPER_API PipelineBuilder {
public:
	PipelineBuilder(const LogicalDevice& dev);
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
	PipelineBuilder& setRasterizationSamples(VkSampleCountFlagBits rasterizationSamples);
	PipelineBuilder& setSampleShadingEnable(VkBool32 sampleShadingEnable);
	PipelineBuilder& setMinSampleShading(float minSampleShading);
	PipelineBuilder& setSampleMask(const VkSampleMask* pSampleMask);
	PipelineBuilder& setAlphaToCoverageEnable(VkBool32 enable);
	PipelineBuilder& setAlphaToOneEnable(VkBool32 enable);

	//VkPipelineColorBlendStateCreateInfo
	PipelineBuilder& setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState>& vec);
	PipelineBuilder& setColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags flags);
	PipelineBuilder& setColorBlendLogicOpEnable(VkBool32 enalbe);
	PipelineBuilder& setColorBlendLogicOp(VkLogicOp op);
	PipelineBuilder& setColorBlendConstants(float d[4]);
	PipelineBuilder& setColorBlendConstants(float,float,float,float);

	//VkPipelineDynamicStateCreateInfo
	PipelineBuilder& setPipelineDynamicStateCreateFlags(VkPipelineDynamicStateCreateFlags flags);
	PipelineBuilder& setDynamicStates(const std::vector<VkDynamicState>& dynamicStates);

	//VkPipelineLayout
	PipelineBuilder& setPipelineLayout(const PipelineLayout& pipelineLayout);

	PipelineBuilder& setRenderPass(RenderPass pass);
	PipelineBuilder& setSubPass(uint32_t id);

	PipelineBuilder& setBasePipelineHandle(Pipeline pipeline);
	PipelineBuilder& setBasePipelineIndex(int32_t index);
private:
	PipelineLayout pipelineLayout;
	LogicalDevice dev;
	RenderPass renderPass;
	uint32_t subpass = 0;
	Pipeline basePipeline;
	int32_t basePipelineIndex = -1;

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

	//VkPipelineColorBlendStateCreateInfo
	std::vector<VkPipelineColorBlendAttachmentState>    colorBlendAttachmentStates;
	VkPipelineColorBlendStateCreateFlags				colorBlendStateCreateflags;
	VkBool32											colorBlendLogicOpEnable;
	VkLogicOp											colorBlendlogicOp;
	float                                               colorBlendConstants[4];

	//VkPipelineDynamicStateCreateInfo
	VkPipelineDynamicStateCreateFlags					dynamicStateCreateFlags;
	std::vector<VkDynamicState>							dynamicStates;
};