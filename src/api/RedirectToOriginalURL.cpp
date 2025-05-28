#include "api/API.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"
#include "Config.hpp"

#include <crow.h>
#include <print>

namespace shurlx::API
{
    void RedirectToOriginalURL(crow::response& res, std::string_view code)
    {
        const auto [result, originalURL] = Database::GetOriginalURL(code);

        std::println("{}", originalURL);

        switch (result)
        {
            case Database::Result::Failure:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("Failed to retrieve original URL due to an internal server error");
                break;

            case Database::Result::NotFound:
                res.code = crow::status::NOT_FOUND;
                res.end("Couldn't find requested original URL");

            case Database::Result::Success:
                res.redirect_perm(originalURL);
                res.end();
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("How the fuck did you get this?");
        }
    }
} // namespace shurlx::API
