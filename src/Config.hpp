#pragma once

#include "utils/Utils.hpp"

namespace shurlx::Config
{
    static const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));
    static const auto BASE_URL = Utils::GetEnv("BASE_URL", std::format("http://localhost:{}", PORT));
    static const auto MAX_SHORT_CODE_LEN = std::stoul(Utils::GetEnv("MAX_SHORT_CODE_LEN", "4"));
    static const auto MAX_REGISTER_ATTEMPTS = std::stoul(Utils::GetEnv("MAX_REGISTER_ATTEMPTS", "16"));
}
