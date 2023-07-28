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
    bool verbose = false;
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

void Request::addHeader(const std::string &header)
{
    d->headers.push_back(header);
}

void Request::addBody(void *data, size_t dataSize)
{
    d->data = data;
    d->dataSize = dataSize;
}

void Request::setVerbose(bool b)
{
    d->verbose = b;
}

void Request::setup(void *p)
{
    CURL* handle = (CURL*)p;
    if (handle) {
        curl_easy_setopt(handle, CURLOPT_URL, d->url.c_str());

        if (d->headers.size()) {
            for (const auto& header : d->headers) {
                d->slist = curl_slist_append(d->slist, header.c_str());
            }

            curl_easy_setopt(handle, CURLOPT_HTTPHEADER, d->slist);
        }

        if (d->data && d->dataSize) {
            curl_easy_setopt(handle, CURLOPT_POSTFIELDS, d->data);
            curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, d->dataSize);

            curl_easy_setopt(handle, CURLOPT_POST, 1L);
        }

        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(handle, CURLOPT_VERBOSE, d->verbose ? 1L : 0L);

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
