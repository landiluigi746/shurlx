#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

#include "utils/Utils.hpp"

int main()
{
    const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](const crow::request& req, crow::response& res) {
        res.set_static_file_info("views/index.html");
        res.end();
    });

    CROW_ROUTE(app, "/click").methods("POST"_method)([](const crow::request& req, crow::response& res) {
        res.end("<h3>You clicked!</h3>");
    });

    app.port(PORT).multithreaded().run();

    return 0;
}
