#pragma once
#include "export.h"
#include <vector>
#include <string>

namespace help {

	VULKAN_WRAPPER_API std::vector<char> readFile(const std::string& filename);

	int log2(uint64_t num);

	//ģ��sql����γɵ�һ��bool���㷽��

}

