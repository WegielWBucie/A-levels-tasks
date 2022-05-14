#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Enter {

private:
    int key;
    int user_ID;
    string date;
    int activity_ID;

public:
    Enter(int &key, int &user_ID, string &date, int &activity_ID) {

        this->key = key;
        this->user_ID = user_ID;
        this->date = date;
        this->activity_ID = activity_ID;
    }
    int getKey() {
        return this->key;
    }
    int getUserID() {
        return this->user_ID;
    }
    string getDate() {
        return this->date;
    }
    int getActivityID() {
        return this->activity_ID;
    }

    static void inputEnters(vector<Enter>&destination, map<int, Enter>&destinationMap) {

        ifstream data;
        data.open("wejscia.txt");
        auto *headers = new string;
        getline(data, *headers);
        delete headers;
        while(!data.eof()) {

            int key, user_ID, activity_ID;
            string date;
            data >> key >> user_ID >> date >> activity_ID;

            auto *enter = new Enter(key, user_ID, date, activity_ID);
            destination.push_back(*enter);
            destinationMap.insert(pair<int, Enter>(key, *enter));

            delete enter;
        }
        data.close();
    }
    static void showEnters(vector<Enter>&destination) {

        for(auto & enter : destination) {
            cout << enter.key << " " << enter.user_ID << " " << enter.date << " " <<
                 enter.activity_ID << endl;
        }
    }
    static void showEnters(map<int, Enter>&destinationMap) {

        for(auto &pair : destinationMap) {
            cout << pair.first << " " << pair.second.key << " " << pair.second.user_ID << " " <<
                pair.second.date << " " << pair.second.activity_ID << endl;
        }
    }
};
