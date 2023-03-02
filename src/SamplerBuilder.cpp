#include "SamplerBuilder.h"
#include "LogicalDevice.h"
#include <stdexcept>

Sampler SamplerBuilder::build() {
	Sampler sampler;
	VkResult suc = vkCreateSampler(dev.dev, &ci, nullptr, &sampler.value());
	if (suc != VK_SUCCESS) {
		throw std::runtime_error("failed to create sampler!");
	}
	return sampler;
}

void SamplerBuilder::setDevice(LogicalDevice d) {
	dev = d;
}

void SamplerBuilder::setSamplerCreateFlags(VkSamplerCreateFlags flags) {
	ci.flags = flags;
}

void SamplerBuilder::setMagFilter(VkFilter filter) {
	ci.magFilter = filter;
}

void SamplerBuilder::setMinFilter(VkFilter filter) {
	ci.minFilter = filter;
}

void SamplerBuilder::setMipmapMode(VkSamplerMipmapMode mode) {
	ci.mipmapMode = mode;
}

void SamplerBuilder::setAddressModeU(VkSamplerAddressMode mode) {
	ci.addressModeU = mode;
}

void SamplerBuilder::setAddressModeV(VkSamplerAddressMode mode) {
	ci.addressModeV = mode;
}

void SamplerBuilder::setAddressModeW(VkSamplerAddressMode mode) {
	ci.addressModeW = mode;
}

void SamplerBuilder::setMipLodBias(float bias) {
	ci.mipLodBias = bias;
}

void SamplerBuilder::setAnisotropyEnable(VkBool32 enable) {
	ci.anisotropyEnable = enable;
}

void SamplerBuilder::setMaxAnisotropy(float anisotropy) {
	ci.maxAnisotropy = anisotropy;
}

void SamplerBuilder::setCompareEnable(VkBool32 compareEnable) {
	ci.compareEnable = compareEnable;
}

void SamplerBuilder::setCompareOp(VkCompareOp op) {
	ci.compareOp = op;
}

void SamplerBuilder::setMinLod(float lod) {
	ci.minLod = lod;
}

void SamplerBuilder::setMaxLod(float lod) {
	ci.maxLod = lod;
}

void SamplerBuilder::setBorderColor(VkBorderColor color) {
	ci.borderColor = color;
}

void SamplerBuilder::setUnNormalizedCoordinates(VkBool32 enable) {
	ci.unnormalizedCoordinates = enable;
}