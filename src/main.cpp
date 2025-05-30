#include <crow.h>
#include <print>

#include "api/API.hpp"
#include "db/Database.hpp"
#include "Config.hpp"
#include "middleware/RateLimiter.hpp"

int main()
{
    shurlx::Database::Init();

    crow::App<shurlx::Middleware::RateLimiter> app;
    crow::mustache::set_global_base("views/");

    CROW_ROUTE(app, "/")
    ([](const crow::request& req, crow::response& res) {
        res.set_static_file_info("views/index.html");
        res.end();
    });

    CROW_ROUTE(app, "/register").methods("POST"_method)(&shurlx::API::RegisterURL);
    CROW_ROUTE(app, "/<string>")(&shurlx::API::RedirectToOriginalURL);

    app.port(shurlx::Config::PORT).multithreaded().run();

    return 0;
}
