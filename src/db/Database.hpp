#pragma once

#include <utility>

namespace shurlx::Database
{
    struct URLModel
    {
        std::string ShortURL;
        std::string OriginalURL;
    };

    enum class Result
    {
        Success,
        NotFound,
        TooManyAttempts,
        Failure
    };

    Result Init();

    std::pair<Result, std::string> RegisterURL(std::string_view originalURL);
    std::pair<Result, std::string> GetOriginalURL(std::string_view shortURL);
} // namespace shurlx::Database
