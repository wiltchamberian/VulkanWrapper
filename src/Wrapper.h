#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "InstanceBuilder.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "SwapChainBuilder.h"
#include "PipelineBuilder.h"

class VULKAN_WRAPPER_API VulkanWrapper {
public:
	bool initEnvironment();
};
