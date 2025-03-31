#include <httplib.h>
#include <sqlite_orm/sqlite_orm.h>

int main()
{
    httplib::Server svr;

    svr.Get("/", [&] (const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello from shurlx!", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
