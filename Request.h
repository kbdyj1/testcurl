#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class RequestPrivate;

class Request {
public:
    Request(const std::string& url = std::string());
    ~Request();

    friend class NetworkManager;

    void setUrl(const std::string& url);
    void addHeader(const std::string& header);
    void addBody(void* data, size_t dataSize);

    void setVerbose(bool);

    virtual void setup(void* handle);
    virtual void setupCallback(void* handle);
    virtual int perform(void* handle);

private:
    RequestPrivate* d;
};

#endif // REQUEST_H
