#include <iostream>
#include <openai/openai.hpp>

int main() {
    std::cout << "Program started\n";
    openai::start();
    std::cout << "OpenAI started\n";

    try {
        auto response = openai::completion().create(R"({
            "model": "text-davinci-003",
            "prompt": "Say this is a test",
            "max_tokens": 7,
            "temperature": 0
        })"_json);
        std::cout << "Response is:\n" << response.dump(2) << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
}
