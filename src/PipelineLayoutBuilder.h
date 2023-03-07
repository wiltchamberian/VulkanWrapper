#pragma once
#include <vector>
#include "PipelineLayout.h"
#include "DescriptorSetLayout.h"
#include "LogicalDevice.h"

class PipelineLayoutBuilder {
public:
	PipelineLayout build();

    void setDevice(LogicalDevice dev);
    void setPipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags flags);
    void setDescriptorSetLayouts(const std::vector<DescriptorSetLayout>& vec);
    void setPushConstantRanges(const std::vector<VkPushConstantRange>& vec);
private:
    LogicalDevice                       dev;
    VkPipelineLayoutCreateFlags         flags;
    std::vector<DescriptorSetLayout>    layouts;
    std::vector<VkPushConstantRange>    pushConstantRanges;
};