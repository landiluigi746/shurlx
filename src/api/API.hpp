#pragma once

namespace crow
{
    struct request;
    struct response;
} // namespace crow

namespace shurlx::API
{
    void RegisterURL(const crow::request& req, crow::response& res);
    void RedirectToOriginalURL(crow::response& res, std::string_view code);
} // namespace shurlx::API
