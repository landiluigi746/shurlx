#pragma once

#include <optional>
#include <string_view>

namespace shurlx::Database
{
    bool Init();

    std::optional<std::string> GetOriginalURL(std::string_view shortURL);
    std::optional<std::string> PutURL(std::string_view originalURL);
    bool DeleteExpiredURLs();
}
