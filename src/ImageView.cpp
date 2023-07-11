#include "ImageView.h"

void ImageView::cleanUp() {
	vkDestroyImageView(dev.dev, view, nullptr);
}