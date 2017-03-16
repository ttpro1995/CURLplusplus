#include <iostream>
#include "CURLplusplus.h"

#include "json/json.h"
#include <sstream>
int main() {

    CURLplusplus client;
    // std::string x = client.Get("https://testcv-a3792.firebaseio.com/result/ui/your_path.json?print=pretty");


   // std::cout << "Hello, World!" << std::endl;
   // std::cout << x<< std::endl;

    // parse json example
    Json::Value jsonData; // create json object

    std::string raw_json = "{ \"meow\" : \"Pusheen\" }";

    // feed string to jsonData
    std::stringstream ss;
    ss << raw_json;
    ss >> jsonData;


    // get the attribute out of json
    std::string cat = jsonData["meow"].asString();
    std::cout << cat << std::endl;

    client.PostJson("https://sleepy-hollows-65143.herokuapp.com/api/result/your_path", raw_json);
    return 0;
}