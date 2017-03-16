//
// Created by Thien on 3/6/2017.
//

#ifndef MEOW_CURLPLUSPLUS_H
#define MEOW_CURLPLUSPLUS_H
#include <curl/curl.h>
#include <string>
#include <stdexcept>
#include <sstream>


class CURLplusplus
{
private:
    CURL* curl;
    std::stringstream ss;
    long http_code;
public:
    CURLplusplus();
    ~CURLplusplus();
    std::string GET(const std::string& url);

    /**
     * @param url: String of url
     * @param jsonString: json as string
     * @return: void
     * */
    std::string POSTjson(const std::string& url, const std::string jsonString);

    long GetHttpCode();

private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
    size_t Write(void *buffer, size_t size, size_t nmemb);
};
#endif //MEOW_CURLPLUSPLUS_H

/*
 *     CURLplusplus client;
 *     std::string x = client.Get("https://servercardevice.herokuapp.com/api/data/latlng");
 * */