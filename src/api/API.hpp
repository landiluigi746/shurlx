#pragma once

namespace crow
{
    struct request;
    struct response;
} // namespace crow

namespace shurlx::API
{
    void RegisterURL(const crow::request& req, crow::response& res);
    void RedirectToOriginalURL(const crow::request& req, crow::response& res);
} // namespace shurlx::API
