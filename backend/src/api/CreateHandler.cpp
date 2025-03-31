#include "api/Api.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <httplib.h>

namespace shurlx::API
{
    void CreateHandler(const httplib::Request& req, httplib::Response& res)
    {
        if(!req.has_param("url"))
        {
            res.set_content("You need to specifiy an URL", "text/plain");
            res.status = httplib::StatusCode::BadRequest_400;
            return;
        }

        const std::string url = req.get_param_value("url");

        if(Utils::IsURLValid(url))
        {
            auto shortened = Database::PutURL(url);

            if(shortened)
            {
                res.set_content(shortened.value(), "text/plain");
                res.status = httplib::StatusCode::OK_200;
            }
            else
            {
                res.set_content("Failed to create a new short URL", "text/plain");
                res.status = httplib::StatusCode::InternalServerError_500;
            }
        }
        else
        {
            res.set_content("Specified URL is not a valid URL", "text/plain");
            res.status = httplib::StatusCode::BadRequest_400;
        }
    }
}
