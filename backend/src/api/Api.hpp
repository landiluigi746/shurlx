#pragma once

namespace httplib
{
    class Request;
    class Response;
}

namespace shurlx::API
{
    void RedirectHandler(const httplib::Request& req, httplib::Response& res);
    void CreateHandler(const httplib::Request& req, httplib::Response& res);
}
