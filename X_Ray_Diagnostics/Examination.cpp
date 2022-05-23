#include <iostream>
#include <fstream>
#include <map>
#include <list>

using namespace std;

class Examination{

private:
    string testID;

public:
    Examination(string &testID) {
        this->testID = testID;
    }

    string getTestID() {
        return this->testID;
    }


    static void inputExaminations(map<string, list<Examination>>&examinations) {
        ifstream data;
        data.open("E:/Informatyczka/ZADANKA/103/badania.txt");
        auto *headers = new string;
        getline(data, *headers);
        delete headers;

        string PESEL;
        string testID;

        while(!data.eof()) {

            data >> PESEL >> testID;

            auto *examination = new Examination(testID);
            if(examinations.find(PESEL) == examinations.end()) {

                 list<Examination>examinationsList;
                 examinationsList.push_back(*examination);
                 examinations.insert(pair<string, list<Examination>>(PESEL, examinationsList));
            }
            else {
                examinations.at(PESEL).push_back(*examination);
            }
            delete examination;
        }
        data.close();
    }
};