#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <stddef.h>

class NetworkManagerPrivate;
class Request;

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    int get(Request& req);
    int post(Request& req);

    const char* errorString(int error);

private:
    NetworkManagerPrivate* d;
};

#endif // NETWORKMANAGER_H
