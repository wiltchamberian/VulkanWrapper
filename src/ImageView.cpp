#include "ImageView.h"

void ImageView::cleanUp() {
	vkDestroyImageView(dev.value(), view, nullptr);
}