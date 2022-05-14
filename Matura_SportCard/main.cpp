#include <iostream>
#include <vector>
#include "Person.cpp"
#include "Enter.cpp"
#include "Activity.cpp"
#include <map>

using namespace std;

int main() {

    vector<Person>people;
    map<int, Person>peopleMap;
    Person::inputPeople(people, peopleMap);

    vector<Enter>enters;
    map<int, Enter>entersMap;
    Enter::inputEnters(enters, entersMap);

    vector<Activity>activities;
    map<int, Activity>activitiesMap;
    Activity::inputActivities(activities, activitiesMap);


    map<int, bool>attendFitnessTBC;
    //ID, ifDidGoAtFitnessTBC

    for(auto person : people) {
        attendFitnessTBC.insert(pair<int, bool>(person.getID(), false));
    }

    cout << "1) " << endl;
    vector<int>fitnessID;
    for(auto activity : activities) {
        if(activity.getActivityType() == "Fitness-TBC") {
            fitnessID.push_back(activity.getActivityID());
        }
    }

    for(auto enter : enters) {
        for(int activityID : fitnessID) {
            if(enter.getActivityID() == activityID) {
                attendFitnessTBC[enter.getUserID()] = true;
            }
        }
    }
    int maleCounter = 0;
    int femaleCounter = 0;
    for(auto pair : attendFitnessTBC) {

        if (pair.second) {
            if(people.at(pair.first - 1).getGender() == 'K') {
                            // -1 because pair.first is being indexed starting from 1
                femaleCounter++;
            } else {
                maleCounter++;
            }
        }
    }
    attendFitnessTBC.clear();
    cout << "Women: " << femaleCounter << "\t Men:  " << maleCounter << endl;

    cout << "2) " << endl;
    map<string, int>generalSum;
    bool alreadyAdded;
    for(auto activity : activities) {

        alreadyAdded = false;
        auto *object = new Object(activity.getPlaceType());
        for(auto& objectAndSum : generalSum) {
            if(objectAndSum.first == object->getObjectType()) {
                alreadyAdded = true;
                break;
            }
        }
        if(!alreadyAdded) {
            generalSum.insert(pair<string, int>(object->getObjectType(), 0));
        }
        delete object;
    }
    for(auto enter : enters) {
        for(auto activity : activities) {
            if(enter.getActivityID() == activity.getActivityID()) {
                generalSum[activity.getPlaceType()] += activity.getPrice();
            }
        }
    }
    cout << "Object" << "\t General sum of prices" << endl;
    for(auto& pair : generalSum) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    generalSum.clear();

    cout << "3) " << endl;
    map<int, int>dailyEntersPerPerson;
    for(auto enter : enters) {

        if(enter.getDate() == "2014-04-16") {

            if(dailyEntersPerPerson.empty()) {
                dailyEntersPerPerson.insert(pair<int,int>(enter.getUserID(), 1));
            }
            else {
                bool create = true;
                for(auto dailyEnter : dailyEntersPerPerson) {
                    if(enter.getUserID() == dailyEnter.first) {
                        dailyEntersPerPerson[dailyEnter.first]++;
                        create = false;
                    }
                }
                if(create){
                    dailyEntersPerPerson.insert(pair<int, int>(enter.getUserID(), 1));
                }
            }
        }
    }
    for(auto dailyEnter : dailyEntersPerPerson) {
        if(dailyEnter.second > 1) {
            cout << peopleMap.at(dailyEnter.first).getSurname() << " " << peopleMap.at(dailyEnter.first).getName() << endl;
        }
    }
    dailyEntersPerPerson.clear();

    cout << "4) " << endl;
    string objectType, activityType;
    int presence, mostPresence = 0;
    vector<int>alreadyVisitedIDs;
    for(auto activity : activitiesMap) {

        presence = 0;
        alreadyVisitedIDs.clear();

        for(auto enter : entersMap) {
            if(enter.second.getActivityID() == activity.second.getActivityID()) {

                if(find(alreadyVisitedIDs.begin(), alreadyVisitedIDs.end(), enter.second.getUserID()) == alreadyVisitedIDs.end()) {
                    alreadyVisitedIDs.push_back(enter.second.getUserID());
                    presence++;
                }
            }
        }

        if(presence > mostPresence) {
            mostPresence = presence;
            objectType = activity.second.getPlaceType();
            activityType = activity.second.getActivityType();
        }
    }
    alreadyVisitedIDs.clear();
    cout << mostPresence << " " << objectType << " " << activityType << endl;

    cout << "5) " << endl;
    map<string, int>objectsEnters;
    for(auto activity : activities) {

        alreadyAdded = false;
        auto *object = new Object(activity.getPlaceType());
        for(auto& objectEnters : objectsEnters) {
            if(objectEnters.first == object->getObjectType()) {
                alreadyAdded = true;
                break;
            }
        }
        if(!alreadyAdded) {
            objectsEnters.insert(pair<string, int>(object->getObjectType(), 0));
        }
        delete object;
    }
    for(auto enter : enters) {

        for(auto activity : activities) {
            if(enter.getActivityID() == activity.getActivityID()) {
                objectsEnters[activity.getPlaceType()]++;
            }
        }
    }
    cout << "Object" << "\t General sum of enters" << endl;
    for(auto &objectEnters : objectsEnters) {
        cout << objectEnters.first << " -> " << objectEnters.second << endl;
    }
    objectsEnters.clear();

    peopleMap.clear();
    entersMap.clear();
    activitiesMap.clear();
}
