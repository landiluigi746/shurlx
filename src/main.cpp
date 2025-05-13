#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([] {
        return "Hello world!";
    });

    app.port(std::stoi(std::getenv("PORT"))).multithreaded().run();

    return 0;
}
