#include "Request.h"
#include <vector>
#include <curl/curl.h>

class RequestPrivate
{
public:
    std::string url;
    std::vector<std::string> headers;
    void* data = nullptr;
    size_t dataSize = 0;
    curl_slist* slist = nullptr;
};

Request::Request(const std::string &url) : d(new RequestPrivate)
{
    setUrl(url);
}

Request::~Request()
{

    delete d;
}

void Request::setUrl(const std::string &url)
{
    d->url = url;
}

void Request::addBody(void *data, size_t dataSize)
{
    d->data = data;
    d->dataSize = dataSize;
}

void Request::setup(void *p)
{
    CURL* handle = (CURL*)p;
    if (handle) {
        curl_easy_setopt(handle, CURLOPT_URL, d->url.c_str());

        for (const auto& header : d->headers) {
            curl_slist_append(d->slist, header.c_str());
        }
        if (d->data && d->dataSize) {
            curl_easy_setopt(handle, CURLOPT_POSTFIELDS, d->data);
            curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, d->dataSize);
        }

        setupCallback(handle);
    }
}

void Request::setupCallback(void *)
{
}

int Request::perform(void *handle)
{
    auto ret = curl_easy_perform(handle);

    curl_slist_free_all(d->slist);

    return ret;
}
