#include "RenderPass.h"
#include "LogicalDevice.h"

void RenderPass::cleanUp() {
	if (dev.isValid()) {
		vkDestroyRenderPass(dev.value(), pass, nullptr);
	}
}

