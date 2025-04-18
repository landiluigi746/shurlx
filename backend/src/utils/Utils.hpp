#pragma once

#include <cstddef>
#include <string>

namespace shurlx::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue);
    bool IsURLValid(const std::string& url);
    std::string RandomString(size_t n);
}
