//#include "library.h"
#include "json.hpp"
#include <iostream>
#include <map>
#include <any>
#include <vector>
using json = nlohmann::json;
int main() {
    json j;
    j["ticker"]={"Si-9.15", "RTS-9.15", "GAZP-9.15"};
    j["id"]={100024, 100027, 100050};
    j["description"]={"Futures contract for USD/RUB",
                      "Futures contract for index RTS",
                      "Futures contract for Gazprom shares"};
    json j1=json::array();
    std::vector <json> v1;
    json obj;
    v1.resize(j["ticker"].size());
    for (size_t i=0;i<j["ticker"].size();i++){
        v1[i]["id"]=j["id"][i];
        v1[i]["ticker"]=j["ticker"][i];
        v1[i]["description"]=j["description"][i];
    }
    for (size_t i=0;i<3;i++){
        j1.push_back(v1[i]);
    }
    std::cout << j1;
    return 0;
}