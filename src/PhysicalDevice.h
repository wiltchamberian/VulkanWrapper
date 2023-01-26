#ifndef __PHYSICAL_DEVICE_H
#define __PHYSICAL_DEVICE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> computeFamily;
	std::optional<uint32_t> transferFamily;
	std::optional<uint32_t> sparseBindingFamily;
	std::optional<uint32_t> protectedFamily;
	bool isComplete(VkQueueFlags flags) {
		if (flags & VK_QUEUE_GRAPHICS_BIT) {
			if (!graphicsFamily.has_value()) return false;
		}
		if (flags & VK_QUEUE_TRANSFER_BIT) {
			if (!transferFamily.has_value()) return false;
		}
		if (flags & VK_QUEUE_COMPUTE_BIT) {
			if (!computeFamily.has_value()) return false;
		}
		if (flags & VK_QUEUE_SPARSE_BINDING_BIT) {
			if (!sparseBindingFamily.has_value()) return false;
		}
		if (flags & VK_QUEUE_PROTECTED_BIT) {
			if (!protectedFamily.has_value()) return false;
		}
		return true;
	}
};

class VULKAN_WRAPPER_API PhysicalDevice {
public:
	bool isValid() {
		return (dev != VK_NULL_HANDLE);
	}
	VkPhysicalDevice dev = VK_NULL_HANDLE;
	QueueFamilyIndices indices;
};

#endif
