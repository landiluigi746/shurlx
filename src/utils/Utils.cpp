#include "Utils.hpp"

#include <random>
#include <chrono>

namespace Utils
{
    static constexpr std::string_view RANDOM_ALPHABET =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    static thread_local std::default_random_engine s_RandEngine(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }

    std::string GetRandomString(size_t n)
    {
        std::string s;
        s.reserve(n);

        std::uniform_int_distribution<> distribution(0, RANDOM_ALPHABET.length());

        for (size_t i = 0; i < n; ++i)
            s.push_back(RANDOM_ALPHABET[distribution(s_RandEngine)]);

        return s;
    }
} // namespace Utils
