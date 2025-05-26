#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <sqlite_orm/sqlite_orm.h>
#include <exception>
#include <print>
#include <utility>

namespace shurlx::Database
{
    using namespace sqlite_orm;

    static const auto MAX_SHORT_URL_LEN = std::stoul(Utils::GetEnv("MAX_SHORT_URL_LEN", "4"));
    static const auto MAX_REGISTER_ATTEMPTS = std::stoul(Utils::GetEnv("MAX_REGISTER_ATTEMPTS", "16"));

    // clang-format off
    static thread_local bool s_Initialized = false;
    static thread_local auto s_DbStorage = make_storage(
        "shurlx.db",
        make_table("URLs",
            make_column("original_url", &URLModel::OriginalURL, primary_key()),
            make_column("short_url", &URLModel::ShortURL, unique())
        )
    );
    // clang-format on

    Result Init()
    {
        if (s_Initialized)
            return Result::Success;

        try
        {
            s_DbStorage.sync_schema();
            s_DbStorage.pragma.journal_mode(journal_mode::WAL);
            s_Initialized = true;
            return Result::Success;
        }
        catch (const std::exception& e)
        {
            std::println("[fatal]: Database::Init() : ", e.what());
            std::abort();
        }
    }

    std::pair<Result, std::string> RegisterURL(std::string_view originalURL)
    {
        if (!s_Initialized)
            Init();

        if (auto existing = s_DbStorage.get_pointer<URLModel>(originalURL))
            return {Result::Success, existing->ShortURL};

        std::string shortURL;

        for (unsigned long i = 0; i < MAX_REGISTER_ATTEMPTS; ++i)
        {
            shortURL = Utils::GetRandomString(static_cast<size_t>(MAX_SHORT_URL_LEN));

            try
            {
                s_DbStorage.transaction([&] mutable {
                    s_DbStorage.insert(into<URLModel>(),
                                       columns(&URLModel::ShortURL, &URLModel::OriginalURL),
                                       values(std::make_tuple(shortURL, originalURL)));
                    return true;
                });
                return {Result::Success, std::move(shortURL)};
            }
            catch (const std::exception& e)
            {
                std::println("[error]: Database::RegisterURL() : ", e.what());
                return {Result::Failure, ""};
            }
        }

        return {Result::TooManyAttempts, ""};
    }

    std::pair<Result, std::string> GetOriginalURL(std::string_view shortURL)
    {
        if (!s_Initialized)
            Init();

        try
        {
            // clang-format off
            if (auto matches = s_DbStorage.select(&URLModel::OriginalURL, where(c(&URLModel::ShortURL) == shortURL)); !matches.empty())
                return {Result::Success, matches[0]};

            return {Result::NotFound, ""};
            // clang-format on
        }
        catch (const std::exception& e)
        {
            std::println("[error]: Database::GetOriginalURL() : ", e.what());
            return {Result::Failure, ""};
        }
    }
} // namespace shurlx::Database
