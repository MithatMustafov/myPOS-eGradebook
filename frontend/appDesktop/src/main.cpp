#include <iostream>
#include "lib/httplib.h"

int main() {
    httplib::Client cli("localhost:3000");
    auto res = cli.Get("/students");

    if (res && res->status == 200) {
        std::cout << "Response body:\n" << res->body << std::endl;
    } else {
        std::cout << "Request failed" << std::endl;
    }

    return 0;
}