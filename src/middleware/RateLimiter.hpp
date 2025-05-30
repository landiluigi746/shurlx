#pragma once

#include <chrono>
#include <cstdint>
#include <mutex>
#include <unordered_map>

namespace crow
{
    struct request;
    struct response;
} // namespace crow

namespace shurlx::Middleware
{
    struct RateLimiter
    {
        struct context
        {
        };

        void before_handle(crow::request& req, crow::response& res, context& ctx);
        void after_handle(crow::request& req, crow::response& res, context& ctx) {}

    private:
        struct ClientInfo
        {
            uint32_t RequestsCount;
            std::chrono::steady_clock::time_point LastSeen;
        };

        std::unordered_map<std::string, ClientInfo> m_ClientMap;
        std::mutex m_Mutex;
    };
} // namespace shurlx::Middleware
