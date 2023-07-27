#include <iostream>
#include "NetworkManager.h"
#include "RequestHtml.h"
#include "RequestMulti.h"

using namespace std;

void test_get(const char* url, const char* filename)
{
    RequestHtml req(url);
    NetworkManager http;

    req.enableProgress(true);

    auto ret = http.get(req);
    if (ret != 0) {
        cerr << "http.get(" << url << "): " << http.errorString(ret) << "\n";
    } else {
        req.write(filename);
    }
}
void test_get_danawa()
{
    const char* url = "https://search.danawa.com/dsearch.php?k1=usb&module=goods&act=dispMain";
    test_get(url, "result.html");
}

void test_get_image()
{
    const char* url = "https://upload.wikimedia.org/wikipedia/commons/c/cc/NewJeans_theMEGASTUDY.jpg";
    test_get(url, "newjeans.jpg");
}

void test_post_multi()
{
    RequestMulti multi;
    char data[] = { 0xa, 0xb, 0xc, 0xd };
    multi.setUrl("http://posthere.com");
    std::string title = "Hello, Qt6";
    multi.addText("title", title);
    multi.addBinary("body", data, 4);

    NetworkManager http;
    int ret = http.post(multi);
    if (ret) {
        std::cout << "http.post(http://posthere.com): " << http.errorString(ret) << "\n";
    }
}

int main()
{
#if (0) //done
    test_post_multi();
#endif

    test_get_image();

    return 0;
}
