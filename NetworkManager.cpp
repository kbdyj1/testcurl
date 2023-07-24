#include "NetworkManager.h"

#include <curl/curl.h>
#include "Request.h"

class NetworkManagerPrivate
{
public:
    NetworkManagerPrivate()
    {
        handle = curl_easy_init();
    }
    ~NetworkManagerPrivate()
    {
        curl_easy_cleanup(handle);
    }

    void reset()
    {
        curl_easy_reset(handle);
    }

    CURL* handle = nullptr;
};

NetworkManager::NetworkManager() : d(new NetworkManagerPrivate)
{
}

NetworkManager::~NetworkManager()
{
    delete d;
}

int NetworkManager::get(Request &req)
{
    d->reset();

    req.setup(d->handle);
    return req.perform(d->handle);
}

int NetworkManager::post(Request &req)
{
    d->reset();

    req.setup(d->handle);
    return req.perform(d->handle);
}

const char *NetworkManager::errorString(int error)
{
    return curl_easy_strerror((CURLcode)error);
}
