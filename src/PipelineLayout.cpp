#include "PipelineLayout.h"
#include "LogicalDevice.h"

void PipelineLayout::cleanUp() {
	if (dev.isValid()) {
		vkDestroyPipelineLayout(dev.value(), pipelineLayout, nullptr);
	}
	
}

void PipelineLayout::Test() {

}

