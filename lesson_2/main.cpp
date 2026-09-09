#include <string>
#include <iostream>

using namespace std;

class UrlParser {
    private:
    string protocol;
    string resource;

    public:
    UrlParser(string protocol, string resource): protocol(protocol), resource(resource) {}

    //  "http://www.example.com/index.html"
    string getUrl() {
        return protocol + "://" + resource;
    }
};

int main() {
    auto urlParser = UrlParser("https", "example.com/index.html");
    cout << "Url is " << urlParser.getUrl() << endl;
}