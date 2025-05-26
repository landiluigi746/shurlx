#include <crow.h>
#include <crow/mustache.h>

#include "api/API.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

int main()
{
    const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));
    shurlx::Database::Init();

    crow::SimpleApp app;
    crow::mustache::set_global_base("views/");

    CROW_ROUTE(app, "/")
    ([](const crow::request& req, crow::response& res) {
        res.set_static_file_info("views/index.html");
        res.end();
    });

    CROW_ROUTE(app, "/register").methods("POST"_method)(&shurlx::API::RegisterURL);

    app.port(PORT).multithreaded().run();

    return 0;
}
