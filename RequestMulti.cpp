#include "RequestMulti.h"
#include <vector>
#include <curl/curl.h>

enum DataType {
    Text = 0,
    Binary,
    File
};

struct Data {
    DataType type;
    std::string name;
    void* data;
    size_t dataSize;
};

class RequestMultiPrivate
{
public:
    curl_mime* mime;
    curl_mimepart* part;
    std::vector<Data> datas;
};


RequestMulti::RequestMulti() : d(new RequestMultiPrivate)
{
}

RequestMulti::~RequestMulti()
{
    delete d;
}

void RequestMulti::addText(const std::string& name, const std::string &str)
{
    d->datas.push_back(Data{Text, name, (void*)str.c_str(), str.size()});
}

void RequestMulti::addBinary(const std::string& name, void *data, size_t dataSize)
{
    d->datas.push_back(Data{Binary, name, data, dataSize});
}

void RequestMulti::addFile(const std::string& name, const std::string &filename)
{
    d->datas.push_back(Data{File, name, (void*)filename.c_str(), filename.size()});
}

void RequestMulti::setup(void *handle, void* data, size_t dataSize)
{
    d->mime = curl_mime_init(handle);
    for (auto& data : d->datas) {
        d->part = curl_mime_addpart(d->mime);

        curl_mime_name(d->part, data.name.c_str());
        switch (data.type) {
        case Text:
            curl_mime_data(d->part, (const char*)data.data, CURL_ZERO_TERMINATED);
            break;
        case Binary:
            curl_mime_data(d->part, (const char*)data.data, data.dataSize);
            break;
        case File:
            curl_mime_filedata(d->part, (const char*)data.data);
            break;
        }
    }
    curl_easy_setopt(handle, CURLOPT_MIMEPOST, d->mime);
}

int RequestMulti::perform(void *handle)
{
    CURLcode res = curl_easy_perform(handle);
    curl_mime_free(d->mime);
    return res;
}
