#include "db/Database.hpp"
#include "db/Models.hpp"
#include "utils/Utils.hpp"

#include <exception>
#include <mutex>
#include <optional>
#include <print>
#include <tuple>
#include <sqlite_orm/sqlite_orm.h>

namespace shurlx::Database
{
    using namespace sqlite_orm;

    static const auto MAX_URL_TIME = std::stoi(Utils::GetEnv("MAX_URL_TIME", "86400"));
    static const auto MAX_RAND_STR_LEN = std::stoi(Utils::GetEnv("MAX_RAND_STR_LEN", "6"));

    static bool s_Initialized = false;
    static auto s_DbStorage = make_storage(":memory:",
        make_table("URLs",
            make_column("OriginalURL", &URLData::OriginalURL, primary_key(), unique()),
            make_column("ShortenedURL", &URLData::ShortenedURL),
            make_column("CreationDate", &URLData::CreationDate, default_value(date("now")))
        ));
    static std::mutex s_DbMutex;

    bool Init()
    {
        if(s_Initialized)
            return true;

        try
        {
            s_DbStorage.sync_schema();
            s_Initialized = true;
            return true;
        }
        catch(const std::exception& e)
        {
            std::println("Exception occurred while initializing database: {}", e.what());
            return false;
        }
    }

    std::optional<std::string> GetOriginalURL(std::string_view shortenedURL)
    {
        if(!s_Initialized)
            return std::nullopt;

        std::lock_guard lock(s_DbMutex);
        if(auto matches = s_DbStorage.select(&URLData::OriginalURL, where(c(&URLData::ShortenedURL) == shortenedURL)); !matches.empty())
            return matches[0];

        return std::nullopt;
    }

    std::optional<std::string> PutURL(std::string_view originalURL)
    {
        if(!s_Initialized)
            return std::nullopt;

        std::lock_guard lock(s_DbMutex);
        if(auto originalMatches = s_DbStorage.get_pointer<URLData>(originalURL))
            return originalMatches->ShortenedURL;

        std::string shortenedURL;

        while(true)
        {
            shortenedURL = Utils::RandomString(MAX_RAND_STR_LEN);

            if(auto matches = s_DbStorage.select(&URLData::ShortenedURL, where(c(&URLData::ShortenedURL) == shortenedURL)); matches.empty())
                break;
        }

        try
        {
            s_DbStorage.insert(
                into<URLData>(),
                columns(&URLData::ShortenedURL, &URLData::OriginalURL),
                values(std::make_tuple(shortenedURL, originalURL)));
            return shortenedURL;
        }
        catch(const std::exception& e)
        {
            std::println("Exception occurred while putting an URL into the database: {}", e.what());
            return std::nullopt;
        }
    }

    bool DeleteExpiredURLs()
    {
        if(!s_Initialized)
            return false;

        try
        {
            std::lock_guard lock(s_DbMutex);
            s_DbStorage.transaction([&]() {
                s_DbStorage.remove_all<URLData>(where((datetime("now") - c(&URLData::CreationDate)) > MAX_URL_TIME));
                return true;
            });
            return true;
        }
        catch(const std::exception& e)
        {
            std::println("Exception occurred while deleting expired URLs from the database: {}", e.what());
            return false;
        }
    }
}
