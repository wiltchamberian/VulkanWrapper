#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include <vector>
#include <optional>
#include <unordered_map>

class VULKAN_WRAPPER_API QueueFamilyIndices {
public:
	bool isComplete(VkQueueFlags flags) {
		const int queueFlagsBitsNum = 8;
		for (int i = 0; i < queueFlagsBitsNum; ++i) {
			if ((1 << i) & flags) {
				if (indexMap.size() < i + 1 || !indexMap[i].has_value()) {
					return false;
				}
			}
		}
		return true;
	}
	std::vector<std::optional<uint32_t>> indexMap;
};

//expand VkQueueFlagBits
enum QueueFlagBits {
	QUEUE_GRAPHICS_BIT = 0x00000001,
	QUEUE_COMPUTE_BIT = 0x00000002,
	QUEUE_TRANSFER_BIT = 0x00000004,
	QUEUE_SPARSE_BINDING_BIT = 0x00000008,
	QUEUE_PROTECTED_BIT = 0x00000010,
	QUEUE_VIDEO_DECODE_BIT_KHR = 0x00000020,
#ifdef VK_ENABLE_BETA_EXTENSIONS
	QUEUE_VIDEO_ENCODE_BIT_KHR = 0x00000040,
#endif
	QUEUE_PRESENT_BIT = 0x00000080,
	QUEUE_OPTICAL_FLOW_BIT_NV = 0x00000100,
	
	QUEUE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

struct SwapChainSupportDetails {
	std::optional<VkSurfaceCapabilitiesKHR> capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};
