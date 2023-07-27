#include "RequestHtml.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

class RequestHtmlPrivate
{
public:
    bool progress = false;
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

    if (d->progress) {
        curl_easy_setopt((CURL*)handle, CURLOPT_NOPROGRESS, 0);
        curl_easy_setopt((CURL*)handle, CURLOPT_PROGRESSDATA, this);
        curl_easy_setopt((CURL*)handle, CURLOPT_PROGRESSFUNCTION, &RequestHtml::staticProgressCallback);
    }
}

size_t RequestHtml::staticWriteCallback(void *data, size_t size, size_t nmemb, void *user)
{
    return ((RequestHtml*)user)->writeCallback(data, size, nmemb);
}

int RequestHtml::staticProgressCallback(void *user, double dlTotal, double dlNow, double upTotal, double upNow)
{
    return ((RequestHtml*)user)->progressCallback(dlTotal, dlNow, upTotal, upNow);
}

int RequestHtml::progressCallback(double dlTotal, double dlNow, double upTotal, double upNow)
{
    std::cout << "progress(download: "
              << (int)dlNow << "/" << (int)dlTotal
              << ", upload: "
              << (int)upNow << "/" << (int)upTotal << "\n";

    return 0;
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

void RequestHtml::enableProgress(bool b)
{
    d->progress = b;
}
