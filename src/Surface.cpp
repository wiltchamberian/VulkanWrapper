#include "Surface.h"

void Surface::cleanUp() {
	vkDestroySurfaceKHR(instance.value(), surface, nullptr);
}
