#include "Semaphore.h"

void Semaphore::cleanUp() {
	vkDestroySemaphore(dev.value(), semaphore, nullptr);
}