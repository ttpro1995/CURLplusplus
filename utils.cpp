//
// Created by Thien on 3/16/2017.
//
#include "utils.h"
#include "json/json.h"

Json::Value parseJson(std::string raw_json){
    // parse json example
    Json::Value jsonData; // create json object
    // feed string to jsonData
    std::stringstream ss;
    ss << raw_json;
    ss >> jsonData;
    return jsonData;
};