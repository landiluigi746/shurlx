#include "api/Api.hpp"
#include "db/Database.hpp"

#include <httplib.h>

int main()
{
    shurlx::Database::Init();

    httplib::Server svr;

    svr.Post("/", [&] (const httplib::Request& req, httplib::Response& res) {
        shurlx::API::CreateHandler(req, res);
    });

    svr.Get("/:url", [&] (const httplib::Request& req, httplib::Response& res) {
        shurlx::API::RedirectHandler(req, res);
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
