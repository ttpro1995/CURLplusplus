#include <iostream>
#include "CURLplusplus.h"
#include "utils.h"
int main() {

    CURLplusplus client;
    std::string x = client.GET("https://httpbin.org/get");
    std::cout <<x << std::endl;


    // parse json example
    Json::Value jsonData = parseJson(x); // create json object

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