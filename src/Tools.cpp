#include "Tools.h"
#include <fstream>

namespace help {
    std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    int log2(uint64_t num) {
        int result = -1;
        int left = 0;
        int right = 63;  // 假设输入为64位整数

        while (left <= right) {
            int mid = left + (right - left) / 2;
            uint64_t power = (1 << mid);

            if (power <= num) {
                result = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return result;
    }
}
