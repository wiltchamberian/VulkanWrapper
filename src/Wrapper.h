#ifndef __WRAPPER_H
#define __WRAPPER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "InstanceBuilder.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "SwapChainBuilder.h"
#include "PipelineBuilder.h"
#include "RenderPassBuilder.h"
#include "SwapChain.h"

class VULKAN_WRAPPER_API VulkanWrapper {
public:
	bool initEnvironment();
};

#endif
