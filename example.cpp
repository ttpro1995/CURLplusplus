#include <iostream>
#include "CURLplusplus.h"

#include "json/json.h"
#include <sstream>
int main() {

    CURLplusplus client;
    std::string x = client.GET("https://httpbin.org/get");
    std::cout <<x << std::endl;


    // parse json example
    Json::Value jsonData; // create json object

    std::string raw_json = x;

    // feed string to jsonData
    std::stringstream ss;
    ss << raw_json;
    ss >> jsonData;


    // get the attribute out of json
    std::string origin = jsonData["origin"].asString();
    std::cout << origin << std::endl;

    // post request example
    std::string cat_json = "{ \"meow\" : \"I am Pusheen the cat\" }";
    std::string post_return = client.POSTjson("http://httpbin.org/post", cat_json);
    std::cout << "POST return" << std::endl;
    std::cout << post_return << std::endl;
    return 0;
}