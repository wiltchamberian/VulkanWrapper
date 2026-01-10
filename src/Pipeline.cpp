#include "Pipeline.h"

void Pipeline::cleanUp() {
	if (dev.isValid()) {
		vkDestroyPipeline(dev.value(), pipeline, nullptr);
	}
}


