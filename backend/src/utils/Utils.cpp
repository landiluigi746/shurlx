#include "utils/Utils.hpp"

#include <chrono>
#include <random>
#include <string_view>
#include <ada.h>

namespace shurlx::Utils
{
    static constexpr std::string_view RANDOM_ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    static thread_local std::default_random_engine s_RandEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val) ? std::string(val) : std::string(defaultValue);
    }

    bool IsURLValid(const std::string& url)
    {
        return (bool) ada::parse(url);
    }

    std::string RandomString(size_t n)
    {
        std::string random;
        random.reserve(n);

        std::uniform_int_distribution<> distribution(0, n);

        for(size_t i = 0; i < n; ++i)
            random.push_back(RANDOM_ALPHABET[distribution(s_RandEngine)]);

        return random;
    }
}
