#pragma once
#include "export.h"
#include <vector>
#include "PipelineLayout.h"
#include "DescriptorSetLayout.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API PipelineLayoutBuilder {
public:
	PipelineLayout build();

    PipelineLayoutBuilder& setDevice(LogicalDevice dev);
    PipelineLayoutBuilder& setPipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags flags);
    PipelineLayoutBuilder& setDescriptorSetLayouts(const std::vector<DescriptorSetLayout>& vec);
    PipelineLayoutBuilder& setPushConstantRanges(const std::vector<VkPushConstantRange>& vec);
private:
    LogicalDevice                       dev;
    VkPipelineLayoutCreateFlags         flags;
    std::vector<DescriptorSetLayout>    layouts;
    std::vector<VkPushConstantRange>    pushConstantRanges;
};