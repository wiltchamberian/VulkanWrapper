#include "Pipeline.h"

VkPipeline& Pipeline::value()
{ 
	return pipeline; 
}

void Pipeline::cleanUp() {
	if (dev.isValid()) {
		vkDestroyPipeline(dev.value(), pipeline, nullptr);
	}
}


