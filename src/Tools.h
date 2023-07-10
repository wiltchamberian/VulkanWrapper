#pragma once
#include "export.h"
#include <vector>
#include <string>

namespace help {

	VULKAN_WRAPPER_API std::vector<char> readFile(const std::string& filename);

	int log2(uint64_t num);

	//模仿sql语句形成的一种bool运算方法

}

