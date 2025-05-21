#include "crow.h"

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

    app.port(PORT).multithreaded().run();

    return 0;
}
