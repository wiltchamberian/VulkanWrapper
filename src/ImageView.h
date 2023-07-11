#ifndef __IMAGE_VIEW_H
#define __IMAGE_VIEW_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API ImageView {
public:
	friend class ImageViewBuilder;
	VkImageView& value() { return view; }
	void cleanUp();
private:
	LogicalDevice dev;
	VkImageView view;
};


#endif