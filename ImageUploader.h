#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include "Request.h"

class ImageUploaderPrivate;

class ImageUploader : public Request
{
public:
    ImageUploader(const std::string& url, const std::string& filename);
    virtual ~ImageUploader();

    static size_t staticReadCallback(void* buf, size_t size, size_t nmemb, void* user);

    void setup(void *handle) override;
    void setupCallback(void *handle) override;
    int perform(void *handle) override;

private:
    ImageUploaderPrivate* d;
};

#endif // IMAGEUPLOADER_H
