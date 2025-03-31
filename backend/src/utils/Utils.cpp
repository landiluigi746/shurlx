#include "utils/Utils.hpp"

#include <random>
#include <regex>
#include <string_view>

namespace shurlx::Utils
{
    static const std::regex URL_PATTERN(R"((http|https)://([a-zA-Z0-9\-\.]+)(:[0-9]+)?(/.*)?)");
    static constexpr std::string_view RANDOM_ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    static std::default_random_engine s_RandEngine;

    bool IsURLValid(const std::string& url)
    {
        return std::regex_match(url, URL_PATTERN);
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
