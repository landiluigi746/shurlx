#include "api/Api.hpp"
#include "db/Database.hpp"

#include <httplib.h>

namespace shurlx::API
{
    void RedirectHandler(const httplib::Request& req, httplib::Response& res)
    {
        if(!req.path_params.contains("url"))
        {
            res.set_content("Request url is empty!", "text/plain");
            res.status = httplib::StatusCode::BadRequest_400;
        }

        const std::string_view url = req.path_params.at("url");
        const auto originalURL = Database::GetOriginalURL(url);

        if(originalURL)
        {
            res.set_redirect(originalURL.value());
            res.status = httplib::StatusCode::MovedPermanently_301;
        }
        else
        {
            res.set_content("Couldn't find requested URL", "text/plain");
            res.status = httplib::StatusCode::NotFound_404;
        }
    }
}
