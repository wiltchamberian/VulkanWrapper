#include "FrameBuffer.h"

void FrameBuffer::cleanUp() {
	if (dev.isValid()) {
		vkDestroyFramebuffer(dev.value(), fb, nullptr);
	}
}