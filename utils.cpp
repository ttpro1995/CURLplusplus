//
// Created by Thien on 3/16/2017.
//
#include "utils.h"


Json parseJson(std::string raw_json){
    // parse json example
    Json jsonData = Json::parse(raw_json) ; // create json object
    // feed string to jsonData
    return jsonData;
};