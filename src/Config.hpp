#pragma once

#include <string>
#include "utils/Utils.hpp"

namespace shurlx::Config
{
    inline const auto PORT = std::stoul(Utils::GetEnv("PORT", "8000"));
    inline const auto BASE_URL = Utils::GetEnv("BASE_URL", std::format("http://localhost:{}", PORT));
    inline const auto MAX_SHORT_CODE_LEN = std::stoul(Utils::GetEnv("MAX_SHORT_CODE_LEN", "4"));
    inline const auto MAX_REGISTER_ATTEMPTS = std::stoul(Utils::GetEnv("MAX_REGISTER_ATTEMPTS", "16"));
    inline const auto REQUESTS_PER_MINUTE = std::stoul(Utils::GetEnv("REQUESTS_PER_MINUTE", "16"));
} // namespace shurlx::Config
