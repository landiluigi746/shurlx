#include "api/Api.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <httplib.h>

int main()
{
    shurlx::Database::Init();

    httplib::Server svr;

    const std::string ORIGIN = shurlx::Utils::GetEnv("ORIGIN", "http://localhost");

    auto setCorsHeaders = [&](httplib::Response& res) {
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
