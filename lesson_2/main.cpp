#include <iostream>
#include <string>
#include <utility>

using namespace std;

class UrlParser {
private:
    string _protocol;
    string _resource;

public:
    UrlParser(string protocol, string resource)
        : _protocol(std::move(protocol)), _resource(std::move(resource)) {}

    //  "http://www.example.com/index.html"
    string getUrl() {
        return _protocol + "://" + _resource;
    }
};

int main() {
    auto urlParser = UrlParser("https", "example.com/index.html");
    cout << "Url is " << urlParser.getUrl() << "\n";
}