//
// Created by Thien on 3/16/2017.
//
#include "json.hpp"
using json = nlohmann::json;

#ifndef CURLPLUSPLUS_UTILS_H
#define CURLPLUSPLUS_UTILS_H

json parseJson(std::string raw_json);

#endif //CURLPLUSPLUS_UTILS_H
