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

struct SwapChainSupportDetails {
	std::optional<VkSurfaceCapabilitiesKHR> capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};
