#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Person {

private:
    int ID;
    string surname;
    string name;
    char gender;

public:
    Person(int ID, string surname, string name, char gender) {
        this->ID = ID;
        this->surname = surname;
        this->name = name;
        this->gender = gender;
    }

    int getID() {
        return this->ID;
    }
    string getSurname() {
        return this->surname;
    }
    string getName() {
        return this->name;
    }
    char getGender() {
        return this->gender;
    }

    static void inputPeople(vector<Person>&destination, map<int, Person> &destinationMap) {

        ifstream data;
        data.open("osoby.txt");
        auto *headers = new string;
        getline(data, *headers);
        delete headers;

        while(!data.eof()) {

            int ID;
            string surname, name;
            char gender;
            data >> ID >> surname >> name >> gender;

            auto *person = new Person(ID, surname, name, gender);
            destination.push_back(*person);
            destinationMap.insert(pair<int, Person>(ID, *person));

            delete person;
        }
        data.close();
    }
    static void showPeople(vector<Person>&destination) {

        for(auto & person : destination) {
            cout << person.ID << " " << person.surname << " " << person.name << " " <<
                person.gender << endl;
        }
    }
    static void showPeople(map<int, Person>&destinationMap) {
        for(auto &pair : destinationMap) {
            cout << pair.first << " "  << pair.second.ID << " " << pair.second.surname << " " <<
                pair.second.name << " " << pair.second.gender << endl;
        }
    }
};
