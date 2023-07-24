#include "RequestHtml.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

class RequestHtmlPrivate
{
public:
    std::string response;
};

RequestHtml::RequestHtml(const std::string& url)
    : Request(url)
    , d(new RequestHtmlPrivate)
{
}

RequestHtml::~RequestHtml()
{
    delete d;
}

void RequestHtml::setupCallback(void *handle)
{
    curl_easy_setopt((CURL*)handle, CURLOPT_WRITEFUNCTION, &RequestHtml::staticWriteCallback);
    curl_easy_setopt((CURL*)handle, CURLOPT_WRITEDATA, this);
}

size_t RequestHtml::staticWriteCallback(void *data, size_t size, size_t nmemb, void *user)
{
    return ((RequestHtml*)user)->writeCallback(data, size, nmemb);
}

size_t RequestHtml::writeCallback(void *data, size_t size, size_t nmemb)
{
    std::cout << "RequestHtml::writeCallback(" << data << ", " << size << ", " << nmemb << ")\n";

    size_t total = size * nmemb;
    d->response.append((const char*)data, total);
    return total;
}

bool RequestHtml::write(const std::string &filename)
{
    std::ofstream os(filename);
    if (os.is_open()) {
        os.write(d->response.data(), d->response.size());
        os.close();

        return true;
    }
    return false;
}
