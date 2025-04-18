#include "api/Api.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <httplib.h>
#include <print>
#include <thread>

int main()
{
    if(!shurlx::Database::Init())
        return 1;

    httplib::Server svr;

    const std::string ORIGIN = shurlx::Utils::GetEnv("ORIGIN", "http://localhost");
    const auto MAX_URL_TIME = std::stoi(shurlx::Utils::GetEnv("MAX_URL_TIME", "86400"));

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

    std::thread deleterThread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(MAX_URL_TIME));

        if(!shurlx::Database::DeleteExpiredURLs())
            std::println("Failed to delete expired URLs");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
