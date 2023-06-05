#include "Shader.h"

Shader& Shader::clearSpecializations() {
	mapEntries.clear();
	return *this;
}

Shader& Shader::addMapEntry(uint32_t constantID, uint32_t offset, size_t siz) {
	VkSpecializationMapEntry mapEntry;
	mapEntry.constantID = constantID;
	mapEntry.offset = offset;
	mapEntry.size = siz;
	mapEntries.push_back(mapEntry);
	return *this;
}

Shader& Shader::popMapEntry() {
	mapEntries.pop_back();
	return *this;
}

Shader& Shader::setConstantData(uint8_t* d, size_t siz) {
	data.clear();
	data.resize(siz);
	std::memcpy(data.data(), d, siz);
	return *this;
}

VkShaderModule Shader::getModule() {
	return module;
}