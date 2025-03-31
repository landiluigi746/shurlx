#pragma once

#include <cstddef>
#include <string>

namespace shurlx::Utils
{
    bool IsURLValid(const std::string& url);
    std::string RandomString(size_t n);
}
