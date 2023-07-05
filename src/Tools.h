#pragma once
#include <vector>
#include <string>

namespace help {

	std::vector<char> readFile(const std::string& filename);

	int log2(uint64_t num);
}

