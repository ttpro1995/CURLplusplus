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
    CURLplusplus()
            : curl(curl_easy_init())
            , http_code(0)
    {

    }
    ~CURLplusplus()
    {
        if (curl) curl_easy_cleanup(curl);
    }
    std::string Get(const std::string& url)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        ss.str("");
        http_code = 0;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return ss.str();
    }

    /**
     * @param url: String of url
     * @param jsonString: json as string
     * @return: void
     * */
    void PostJson(const std::string& url, const std::string jsonString){
        CURL *curl;
        CURLcode res;

        /* In windows, this will init the winsock stuff */
        curl_global_init(CURL_GLOBAL_ALL);

        // application/json
        struct curl_slist *headers=NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        /* get a curl handle */
        curl = curl_easy_init();
        if(curl) {
            /* First set the URL that is about to receive our POST. This URL can
               just as well be a https:// URL if that is what should receive the
               data. */
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            /* Now specify the POST data */
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\n"
                    "  \"meow\" : \"I am Stormy the cat\"\n"
                    "}");

            /*Set header*/
            /* pass our list of custom made headers */
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            /* Check for errors */
            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

            /* always cleanup */
            curl_slist_free_all(headers); /* free the header list */
            curl_easy_cleanup(curl);
        }
    }

    long GetHttpCode()
    {
        return http_code;
    }
private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
    }
    size_t Write(void *buffer, size_t size, size_t nmemb)
    {
        ss.write((const char*)buffer,size*nmemb);
        return size*nmemb;
    }
};
#endif //MEOW_CURLPLUSPLUS_H

/*
 *     CURLplusplus client;
 *     std::string x = client.Get("https://servercardevice.herokuapp.com/api/data/latlng");
 * */