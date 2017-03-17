//
// Created by Thien on 3/16/2017.
//

#include "CURLplusplus.h"

CURLplusplus::CURLplusplus()
        : curl(curl_easy_init())
        , http_code(0)
{

}

CURLplusplus::~CURLplusplus()
{
    if (curl) curl_easy_cleanup(curl);
}

size_t CURLplusplus::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
}
size_t CURLplusplus::Write(void *buffer, size_t size, size_t nmemb)
{
    ss.write((const char*)buffer,size*nmemb);
    return size*nmemb;
}

std::string CURLplusplus::GET(const std::string& url)
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
    std::string result = ss.str();
    ss.str(""); // clear ss
    return result;
}

std::string CURLplusplus::POSTjson(const std::string& url, const std::string jsonString){
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
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);

        /*Set header*/
        /* pass our list of custom made headers */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_slist_free_all(headers); /* free the header list */
        curl_easy_cleanup(curl);
        std::string result = ss.str();
        ss.str(""); // clear ss
        return result;
    }
}

long CURLplusplus::GetHttpCode()
{
    return http_code;
}