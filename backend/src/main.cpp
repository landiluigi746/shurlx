#include "api/Api.hpp"
#include "db/Database.hpp"

#include <httplib.h>

#ifndef ORIGIN
#define ORIGIN "http://localhost"
#endif

int main()
{
    shurlx::Database::Init();

    httplib::Server svr;

    auto setCorsHeaders = [](httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", ORIGIN);
        res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept, Origin, Authorization");
        res.set_header("Access-Control-Allow-Methods", "OPTIONS, GET, POST, HEAD");
    };

    svr.Options("/", [&] (const httplib::Request& req, httplib::Response& res) {
        setCorsHeaders(res);
        res.status = 204;
    });

    svr.Options("/:url", [&] (const httplib::Request& req, httplib::Response& res) {
        setCorsHeaders(res);
        res.status = 204;
    });

    svr.Post("/", [&] (const httplib::Request& req, httplib::Response& res) {
        setCorsHeaders(res);
        shurlx::API::CreateHandler(req, res);
    });

    svr.Get("/:url", [&] (const httplib::Request& req, httplib::Response& res) {
        setCorsHeaders(res);
        shurlx::API::RedirectHandler(req, res);
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
