#ifndef REQUESTMULTI_H
#define REQUESTMULTI_H

#include "Request.h"

class RequestMultiPrivate;

class RequestMulti : public Request
{
public:
    RequestMulti();
    virtual ~RequestMulti();

    void addText(const std::string& name, const std::string& str);
    void addBinary(const std::string& name, void* data, size_t dataSize);
    void addFile(const std::string& name, const std::string& filename);

    void setup(void* handle, void* data, size_t dataSize) override;
    int perform(void *handle) override;

private:
    RequestMultiPrivate* d;
};

#endif // REQUESTMULTI_H
