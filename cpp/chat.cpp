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

    while (true)
    {
        std::string input;
        std::cout << "You: ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        nlohmann::json body_json = {
            {"model", "gpt-4o-mini"},
            {"input", input}
        };
        std::string body = body_json.dump();

        auto res = cli.Post("/v1/responses", body, "application/json");

        if (res) {
            //std::cout << res->body << '\n';
            auto json = nlohmann::json::parse(res->body);

            std::string text = json["output"][0]["content"][0]["text"];
            std::cout << "GPT: " << text << '\n';
        } else {
            std::cerr << "Request failed.\n";
        }
    }
    return 0;
}