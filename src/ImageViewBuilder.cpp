#include "ImageViewBuilder.h"
#include "ImageView.h"
#include <stdexcept>


ImageViewBuilder::ImageViewBuilder(LogicalDevice device)
:dev(device)
{


}

ImageView ImageViewBuilder::build() {
	ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ci.pNext = nullptr;
	ImageView imageview;
	if (vkCreateImageView(dev.value(), &ci, nullptr, &imageview.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image views!");
	}
	else {
		imageview.dev = dev;
	}
	return imageview;
}

ImageViewBuilder& ImageViewBuilder::setImageViewCreateFlags(VkImageViewCreateFlags flags) {
	ci.flags = flags;
	return *this;
}

ImageViewBuilder& ImageViewBuilder::setImage(VkImage image) {
	ci.image = image;
	return *this;
}

ImageViewBuilder& ImageViewBuilder::setFormat(VkFormat format) {
	ci.format = format;
	return *this;
}

ImageViewBuilder& ImageViewBuilder::setImageViewType(VkImageViewType type) {
	ci.viewType = type;
	return *this;
}

ImageViewBuilder& ImageViewBuilder::setComponentMapping(VkComponentMapping cmMapping) {
	ci.components = cmMapping;
	return *this;
}

ImageViewBuilder& ImageViewBuilder::setImageSubresourceRange(VkImageSubresourceRange subresourceRange) {
	ci.subresourceRange = subresourceRange;
	return *this;
}