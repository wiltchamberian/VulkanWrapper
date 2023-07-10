#include "Pipeline.h"

void Pipeline::cleanUp() {
	if (dev.isValid()) {
		vkDestroyPipeline(dev.dev, pipeline, nullptr);
	}
}

