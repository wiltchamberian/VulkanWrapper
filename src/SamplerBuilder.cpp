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

SamplerBuilder& SamplerBuilder::setDevice(LogicalDevice d) {
	dev = d;
	return *this;
}

SamplerBuilder& SamplerBuilder::setSamplerCreateFlags(VkSamplerCreateFlags flags) {
	ci.flags = flags;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMagFilter(VkFilter filter) {
	ci.magFilter = filter;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMinFilter(VkFilter filter) {
	ci.minFilter = filter;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMipmapMode(VkSamplerMipmapMode mode) {
	ci.mipmapMode = mode;
	return *this;
}

SamplerBuilder& SamplerBuilder::setAddressModeU(VkSamplerAddressMode mode) {
	ci.addressModeU = mode;
	return *this;
}

SamplerBuilder& SamplerBuilder::setAddressModeV(VkSamplerAddressMode mode) {
	ci.addressModeV = mode;
	return *this;
}

SamplerBuilder& SamplerBuilder::setAddressModeW(VkSamplerAddressMode mode) {
	ci.addressModeW = mode;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMipLodBias(float bias) {
	ci.mipLodBias = bias;
	return *this;
}

SamplerBuilder& SamplerBuilder::setAnisotropyEnable(VkBool32 enable) {
	ci.anisotropyEnable = enable;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMaxAnisotropy(float anisotropy) {
	ci.maxAnisotropy = anisotropy;
	return *this;
}

SamplerBuilder& SamplerBuilder::setCompareEnable(VkBool32 compareEnable) {
	ci.compareEnable = compareEnable;
	return *this;
}

SamplerBuilder& SamplerBuilder::setCompareOp(VkCompareOp op) {
	ci.compareOp = op;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMinLod(float lod) {
	ci.minLod = lod;
	return *this;
}

SamplerBuilder& SamplerBuilder::setMaxLod(float lod) {
	ci.maxLod = lod;
	return *this;
}

SamplerBuilder& SamplerBuilder::setBorderColor(VkBorderColor color) {
	ci.borderColor = color;
	return *this;
}

SamplerBuilder& SamplerBuilder::setUnNormalizedCoordinates(VkBool32 enable) {
	ci.unnormalizedCoordinates = enable;
	return *this;
}