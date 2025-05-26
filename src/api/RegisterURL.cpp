#include "api/API.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <crow.h>
#include <crow/mustache.h>
#include <print>

namespace shurlx::API
{
    void RegisterURL(const crow::request& req, crow::response& res)
    {
        const auto bodyParams = req.get_body_params();

        auto resultHTML = crow::mustache::load("result.html");
        crow::mustache::context ctx;

        if (bodyParams.get("url") == nullptr)
        {
            res.code = crow::status::BAD_REQUEST;
            ctx["error"] = true;
            ctx["message"] = "You need to specify an URL";
            res.end(resultHTML.render(ctx).dump());
            return;
        }

        const std::string_view url = bodyParams.get("url");

        if (!Utils::IsURL(url))
        {
            res.code = crow::status::BAD_REQUEST;
            ctx["error"] = true;
            ctx["message"] = "Specified \"url\" is not a valid URL";
            res.end(resultHTML.render(ctx).dump());
            return;
        }

        auto [result, shortCode] = Database::RegisterURL(url);

        switch (result)
        {
            case Database::Result::TooManyAttempts:
            case Database::Result::Failure:
                ctx["error"] = true;
                ctx["message"] = "Failed to register the URL due to an internal server error";
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                break;

            case Database::Result::Success:
                ctx["error"] = false;
                ctx["shortURL"] = shortCode;
                break;

            default:
                ctx["error"] = true;
                ctx["message"] = "How the fuck did you get this?";
                res.code = crow::status::INTERNAL_SERVER_ERROR;
        }

        res.end(resultHTML.render(ctx).dump());
    }
} // namespace shurlx::API
