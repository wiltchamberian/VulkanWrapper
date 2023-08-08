#ifndef __WRAPPER_H
#define __WRAPPER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "InstanceBuilder.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "SwapChainBuilder.h"
#include "PipelineBuilder.h"
#include "PipelineLayoutBuilder.h"
#include "RenderPassBuilder.h"
#include "SwapChain.h"
#include "SurfaceBuilder.h"
#include "ShaderStageBuilder.h"
#include "FrameBufferBuilder.h"
#include "FrameBuffer.h"
#include "ImageViewBuilder.h"
#include "Tools.h"
#include "SemaphoreBuilder.h"
#include "FenceBuilder.h"
#include "CommandPoolBuilder.h"
#include "CommandPool.h"
#include "CommandBuffer.h"


class VULKAN_WRAPPER_API VulkanWrapper {
public:
	bool initEnvironment();
};

#endif
