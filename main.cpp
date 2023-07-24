#include <iostream>
#include "NetworkManager.h"
#include "RequestHtml.h"

using namespace std;

void test_get(const char* url, const char* filename)
{
    RequestHtml req(url);
    NetworkManager http;

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

int main()
{
    test_get_image();

    return 0;
}
