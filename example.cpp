#include <iostream>
#include "CURLplusplus.h"
#include "utils.h"
int main() {

    CURLplusplus client;
    std::string x = client.GET("https://httpbin.org/get");
    std::cout <<"HTTP get result" << std::endl;
    std::cout <<x << std::endl;


    // parse json example
    Json jsonData = parseJson(x); // create json object

    // get the attribute out of json
    std::string origin = jsonData["origin"];
    std::cout << origin << std::endl;

    // create json
    Json cat_json;
    cat_json["unixtime"] = time(nullptr);
    cat_json["meow"] = "I am Pusheen the cat";
    cat_json["likes"] = {"cookies", "netflex"};

    // post request example
    std::string cat_json_string = cat_json.dump();
    std::string post_return = client.POSTjson("http://httpbin.org/post", cat_json_string);
    std::cout << "POST return" << std::endl;
    std::cout << post_return << std::endl;
    return 0;
}