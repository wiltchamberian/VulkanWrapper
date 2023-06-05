#pragma once

#include "Pipeline.h"
#include "PipelineLayout.h"
#include "LogicalDevice.h"
#include "RenderPass.h"
#include "Shader.h"
#include <string>

class VULKAN_WRAPPER_API PipelineBuilder {
public:
	
	Pipeline build();

	void setShaders(const std::vector<Shader>& shaders);

	//VkPipelineVertexInputStateCreateInfo
	void setVertexInputBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vec);
	void setVertexInputAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vec);

	//VkPipelineInputAssemblyStateCreateInfo
	void setPrimitiveTopology(VkPrimitiveTopology topology);
	void setAssemblyStateCreateFlags(VkPipelineInputAssemblyStateCreateFlags flags);
	void setPrimitiveRestartEnable(VkBool32 enable);

	//VkPipelineViewportStateCreateInfo
	void setViewportStateCreateFlags(VkPipelineViewportStateCreateFlags flags);
	void setViewports(const std::vector<VkViewport>& viewports);
	void setScissors(const std::vector<VkRect2D>& scirros);

	//VkPipelineRasterizationStateCreateInfo
	void setRasterizationStateCreateFlags(VkPipelineRasterizationStateCreateFlags flags);
	void setDepthClampEnable(VkBool32 enable);
	void setRasterizerDiscardEnable(VkBool32 enalbe);
	void setPolygonMode(VkPolygonMode mode);
	void setCullMode(VkCullModeFlags flags);
	void setFrontFace(VkFrontFace face);
	void setDepthBiasEnable(VkBool32 enable);
	void setDepthBiasConstantFactor(float factor);
	void setDepthBiasClamp(float factor);
	void setDepthBiasSlopeFactor(float slopFactor);
	void setLineWidth(float lineWidth);

	//VkPipelineMultisampleStateCreateInfo
	void setMultisampleStateCreateFlags(VkPipelineMultisampleStateCreateFlags flags);
	void setSampleCountFlagBits(VkSampleCountFlagBits rasterizationSamples);
	void setSampleShadingEnable(VkBool32 sampleShadingEnable);
	void setMinSampleShading(float minSampleShading);
	void setSampleMASK(const VkSampleMask* pSampleMask);
	void setAlphaToCoverageEnable(VkBool32 enable);
	void setAlphaToOneEnable(VkBool32 enable);

	//VkPipelineColorBlendCreateInfo
	void setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState>& vec);
	void setColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags flags);
	void setColorBlendLogicOpEnable(VkBool32 enalbe);
	void setColorBlendLogicOp(VkLogicOp op);
	void setColorBlendConstants(float d[4]);
	//void setBlendEnable(VkBool32 enable);
	//void setSrcColorBlendFactor(VkBlendFactor factor);
	//void setDstColorBlendFactor(VkBlendFactor factor);
	//void setColorBlendOp(VkBlendOp op);
	//void setSrcAlphaBlendFactor(VkBlendFactor factor);
	//void setDstAlphaBlendFactor(VkBlendFactor factor);
	//void setAlphaBlendOp(VkBlendOp op);
	//void setColorComponentFlags(VkColorComponentFlags colorWriteMask);

	//VkPipelineDynamicStateCreateInfo
	void setPipelineDynamicStateCreateFlags(VkPipelineDynamicStateCreateFlags flags);
	void setDynamicStates(const std::vector<VkDynamicState>& dynamicStates);

	//VkPipelineLayout
	void setPipelineLayout(const PipelineLayout& pipelineLayout);
private:
	PipelineLayout pipelineLayout;
	LogicalDevice dev;
	RenderPass renderPass;

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
	const VkSampleMask*					     pSampleMask;
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