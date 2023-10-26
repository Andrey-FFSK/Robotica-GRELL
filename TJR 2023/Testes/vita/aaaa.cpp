#include <iostream>
#include <string>

using namespace std;

int main() {
    unsigned long mills = 13500;
    int secst = mills/1000;
    int mins = secst/60;
    int secs = secst - (mins * 60);
    cout << "millis: " << mills << endl;
    cout << mins << ":" << secs << endl;

    mills = 38219021;
    secst = mills/1000;
    mins = secst/60;
    secs = secst - (mins * 60);
    cout << "millis: " << mills << endl;
    cout << mins << ":" << secs << endl;

    return 0;
}