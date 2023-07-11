#include "Surface.h"

void Surface::cleanUp() {
	if (instance.isValid()) {
		vkDestroySurfaceKHR(instance.value(), surface, nullptr);
	}
}
