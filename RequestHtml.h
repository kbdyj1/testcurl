#ifndef REQUESTHTML_H
#define REQUESTHTML_H

#include "Request.h"

class RequestHtmlPrivate;

class RequestHtml : public Request
{
public:
    RequestHtml(const std::string& url);
    virtual ~RequestHtml();

    static size_t staticWriteCallback(void* data, size_t size, size_t nmemb, void* user);

    virtual void setupCallback(void *handle) override;

    size_t writeCallback(void* data, size_t size, size_t nmemb);

    bool write(const std::string& filename);

private:
    RequestHtmlPrivate* d;
};

#endif // REQUESTHTML_H
