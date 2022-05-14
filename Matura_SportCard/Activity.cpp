#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Activity {

private:
    int activity_ID;
    string placeType;
    string activityType;
    int price;

public:
    Activity(int &activity_ID, string &placeType, string &activityType, int &price) {
        this->activity_ID = activity_ID;
        this->placeType = placeType;
        this->activityType = activityType;
        this->price = price;
    }
    int getActivityID() {
        return this->activity_ID;
    }
    string getPlaceType() {
        return this->placeType;
    }
    string getActivityType() {
        return this->activityType;
    }
    int getPrice() {
        return this->price;
    }

    static void inputActivities(vector<Activity>&destination, map<int, Activity>&destinationMap) {

        ifstream data;
        data.open("zajecia.txt");
        auto *headers = new string;
        getline(data, *headers);
        delete headers;
        while(!data.eof()) {

            int activity_ID, price;
            string placeType, activityType;

            data >> activity_ID >> placeType >> activityType >> price;

            auto *activity = new Activity(activity_ID, placeType, activityType, price);
            destination.push_back(*activity);
            destinationMap.insert(pair<int, Activity>(activity_ID, *activity));
            delete activity;
        }
        data.close();
    }
    static void showActivities(vector<Activity>&destination) {

        for(auto & activity : destination) {
            cout << activity.activity_ID << " " << activity.placeType << " " <<
                activity.activityType << " " << activity.price << endl;
        }
    }
    static void showActivities(map<int, Activity>&destinationMap) {

        for(auto &pair : destinationMap) {
            cout << pair.first << " " << pair.second.activity_ID << " " << pair.second.placeType << " " <<
                pair.second.activityType << " " << pair.second.price << endl;
        }
    }
};

class Object {

private:
    string objectType;

public:
    explicit Object (string objectType) {
        this->objectType = objectType;
    }

    string getObjectType() const {
        return objectType;
    }
};

