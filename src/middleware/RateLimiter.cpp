#include "middleware/RateLimiter.hpp"
#include "Config.hpp"

#include <chrono>
#include <crow.h>

namespace shurlx::Middleware
{
    static constexpr auto WINDOW_TIME = std::chrono::minutes(1);

    void RateLimiter::before_handle(crow::request& req, crow::response& res, context& ctx)
    {
        const std::string ip = req.remote_ip_address;
        const auto now = std::chrono::steady_clock::now();

        std::lock_guard lock(m_Mutex);

        if (!m_ClientMap.contains(ip))
        {
            m_ClientMap.emplace(ip, ClientInfo{1, std::chrono::steady_clock::now()});
            return;
        }

        ClientInfo& clientInfo = m_ClientMap[ip];

        if (now - clientInfo.LastSeen >= WINDOW_TIME)
        {
            clientInfo.RequestsCount = 1;
            clientInfo.LastSeen = now;
        }

        // clang-format off
        if (clientInfo.RequestsCount > Config::REQUESTS_PER_MINUTE)
        {
            auto invalidHTML = crow::mustache::load("invalid.html");

            res.code = crow::status::TOO_MANY_REQUESTS;
            res.add_header(
                "Retry-After",
                std::to_string(std::chrono::duration_cast<std::chrono::seconds>(WINDOW_TIME).count())
            );

            res.end(invalidHTML.render({
                {"message", "Too many requests. Please try again later"}
            }).dump());
            return;
        }
        // clang-format on

        ++clientInfo.RequestsCount;
    }
} // namespace shurlx::Middleware
