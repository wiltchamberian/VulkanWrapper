#ifndef __IMAGE_VIEW_BUILDER_H
#define __IMAGE_VIEW_BUILDER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class ImageView;

class VULKAN_WRAPPER_API ImageViewBuilder {
public:
	ImageViewBuilder();
	ImageViewBuilder(LogicalDevice device);
	ImageView build();
	ImageViewBuilder& setDevice(LogicalDevice device);
	ImageViewBuilder& setImageViewCreateFlags(VkImageViewCreateFlags flags);
	ImageViewBuilder& setImage(VkImage image);
	ImageViewBuilder& setFormat(VkFormat format);
	ImageViewBuilder& setImageViewType(VkImageViewType type);
	ImageViewBuilder& setComponentMapping(VkComponentMapping type);
	ImageViewBuilder& setImageSubresourceRange(VkImageSubresourceRange type);
private:
	LogicalDevice dev;
	VkImageViewCreateInfo ci{};
};

#endif