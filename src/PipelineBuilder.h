#pragma once

#include "Pipeline.h"
#include "LogicalDevice.h"
#include "RenderPass.h"
#include <string>

class VULKAN_WRAPPER_API PipelineBuilder {
public:
	VkShaderModule createShaderModule(const std::vector<char>& code);
	Pipeline build();

	void setVertexShaderPath(const std::string& code);
	void setFragmentShaderPath(const std::string& code);
	void setGeometryShaderPath (const std::string& code);
	void setComputeShaderPath(const std::string& code);

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

	//
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
private:
	VkPipelineLayout layout;
	LogicalDevice dev;
	RenderPass renderPass;

	std::string vertexPath;
	std::string fragmentPath;
	std::string geometryPath;
	std::string computePath;

	std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;

	VkPipelineInputAssemblyStateCreateFlags assemblyStateCreateFlags;
	VkPrimitiveTopology topology;
	VkBool32  primitiveRestartEnable;

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
};