#include "SemaphoreBuilder.h"
#include <stdexcept>

SemaphoreBuilder::SemaphoreBuilder(LogicalDevice d)
:dev(d)
{
	ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	ci.pNext = nullptr;
}

Semaphore SemaphoreBuilder::build() {
	Semaphore semaphore;
	if (vkCreateSemaphore(dev.value(), &ci, nullptr, &semaphore.value()) != VK_SUCCESS){
		throw std::runtime_error("failed to create semaphores!");
	}
	else {
		semaphore.dev = dev;
	}
	return semaphore;
}

SemaphoreBuilder& SemaphoreBuilder::setSemaphoreCreateFlags(VkSemaphoreCreateFlags flags) {
	ci.flags = flags;
	return *this;
}