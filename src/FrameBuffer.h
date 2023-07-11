#ifndef __FRAME_BUFFER_H
#define __FRAME_BUFFER_H

#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API FrameBuffer {
public:
	friend class FrameBufferBuilder;
	VkFramebuffer& value() { return fb; }
private:
	LogicalDevice dev;
	VkFramebuffer fb;
};

#endif