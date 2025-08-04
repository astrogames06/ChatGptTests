#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

int main() {
    std::cout << "Start!\n";
    std::string api_key = std::getenv("OPENAI_API_KEY");

    httplib::SSLClient cli("api.openai.com");
    cli.set_default_headers({
        {"Content-Type", "application/json"},
        {"Authorization", "Bearer " + api_key}
    });

    std::string input;
    std::cout << "Image: ";
    std::getline(std::cin, input);

    std::string body = R"({
        "model": "dall-e-2",
        "prompt": "})" + input + R"({",
        "n": 1,
        "size": "1024x1024"
    })";

    auto res = cli.Post("/v1/images/generations", body, "application/json");

    if (res) {
        auto json = nlohmann::json::parse(res->body);
        std::string url = json["data"][0]["url"];
        std::cout << url << '\n';

        size_t pos_scheme = url.find("://");
        size_t pos_host_end = url.find('/', pos_scheme + 3);
        std::string host = url.substr(pos_scheme + 3, pos_host_end - (pos_scheme + 3));
        std::string path = url.substr(pos_host_end);

        std::cout << "host: " << host << "\n path: " << path << '\n';

        httplib::SSLClient img_cli(host);

        auto img_res = img_cli.Get(path.c_str());

        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

        std::ofstream out(input + ".png", std::ios::binary);
        out << img_res->body;
        out.close();
    } else {
        std::cerr << "Request failed.\n";
    }

    return 0;
}