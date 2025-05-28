#include "api/API.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"
#include "Config.hpp"

#include <crow.h>

namespace shurlx::API
{
    void RedirectToOriginalURL(crow::response& res, std::string_view code)
    {
        const auto [result, originalURL] = Database::GetOriginalURL(code);

        auto invalidHTML = crow::mustache::load("invalid.html");
        crow::mustache::context ctx;

        switch (result)
        {
            case Database::Result::Failure:
                ctx["message"] = "Failed to retrieve original URL due to an internal server error";
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end(invalidHTML.render(ctx).dump());
                break;

            case Database::Result::NotFound:
                ctx["message"] = "Couldn't find requested original URL";
                res.code = crow::status::NOT_FOUND;
                res.end(invalidHTML.render(ctx).dump());

            case Database::Result::Success:
                res.redirect_perm(originalURL);
                res.end();
                break;

            default:
                ctx["message"] = "How the fuck did you get this?";
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end(invalidHTML.render(ctx).dump());
        }
    }
} // namespace shurlx::API
