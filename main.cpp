#include <iostream>
#include "headers/WebserverClient.hpp"

WebserverClient ws{};

int main() {
    std::cout << "Hello world" << std::endl;
    ws.create_account("sumeet", "sumeet.singhji@outlook.com", "password1");
    return 0;
}