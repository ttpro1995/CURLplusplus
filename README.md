# CURLplusplus
### an easy curl wrapper

[![Build Status](https://travis-ci.org/ttpro1995/CURLplusplus.svg?branch=master)](https://travis-ci.org/ttpro1995/CURLplusplus)

GET

```cpp
    CURLplusplus client;
    std::string x = client.GET("https://httpbin.org/get");
    std::cout <<x << std::endl;
```

POSTjson with Content-Type: application/json

```cpp
    // post request example
    std::string cat_json = "{ \"meow\" : \"I am Pusheen the cat\" }";
    std::string post_return = client.POSTjson("http://httpbin.org/post", cat_json);
    std::cout << "POST return" << std::endl;
    std::cout << post_return << std::endl;
    return 0;
```