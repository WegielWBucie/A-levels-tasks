#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class XRay {

private:
    string testName;
    int cost;

public:
    XRay(string &testName, int &cost)  {
        this -> testName = testName;
        this -> cost = cost;
    }
    string getTestName() {
        return this->testName;
    }
    int getCost() {
        return this->cost;
    }

    static void inputXRays(map<string, XRay>&xRays) {
        ifstream data;
        data.open("E:/Informatyczka/ZADANKA/103/rtg.txt");

        auto *headers = new string;
        getline(data, *headers);
        delete headers;

        int cost;
        string testID, testName;

        while(!data.eof()) {

            data >> testID >> testName >> cost;

            auto xRay = new XRay(testName, cost);
            xRays.insert(pair<string, XRay>(testID, *xRay));
            delete xRay;

        }
        data.close();
    }

};