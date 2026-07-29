#include <iostream>
#include <nlohmann/json.hpp>

int main()
{
    using json = nlohmann::json;

    json document;

    document["Name"] = "OPTIER";
    document["Version"] = "1.0";

    std::cout << document.dump(4) << '\n';

    return 0;
}