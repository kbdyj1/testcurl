#include "ImageUploader.h"
#include <curl/curl.h>
#include <fstream>

class ImageUploaderPrivate
{
public:
    void* data;
    size_t dataSize;
};


ImageUploader::ImageUploader(const std::string &url, const std::string &filename)
    : Request(url)
    , d(new ImageUploaderPrivate)
{
    std::ifstream is(filename);
    if (is.is_open()) {
        is.seekg(0, std::ios::end);
        size_t len = is.tellg();
        is.seekg(0, std::ios::beg);

        d->data = new char[len];
        d->dataSize = len;

        is.read((char*)d->data, d->dataSize);
    }
}

ImageUploader::~ImageUploader()
{
    if (d->dataSize) {
        delete [] (char*)d->data;
    }
    delete d;
}

size_t ImageUploader::staticReadCallback(void *buf, size_t size, size_t nmemb, void *user)
{
    size_t total = size * nmemb;

    return total;
}

void ImageUploader::setup(void *handle)
{
    Request::setup(handle);

    curl_easy_setopt(handle, CURLOPT_UPLOAD, 1L);
}

void ImageUploader::setupCallback(void *handle)
{
    curl_easy_setopt(handle, CURLOPT_READFUNCTION, &ImageUploader::staticReadCallback);
    curl_easy_setopt(handle, CURLOPT_READDATA, d->data);
    curl_easy_setopt(handle, CURLOPT_INFILESIZE_LARGE, d->dataSize);
}

int ImageUploader::perform(void *handle)
{
    return curl_easy_perform(handle);
}
