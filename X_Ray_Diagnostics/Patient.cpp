#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class Patient {

private:
    string surname;
    string name;
    string secondName;
    char gender;
    string ward;

public:
    Patient(string &surname, string &name, string &secondName, char &gender, string &ward) {
        this -> surname = surname;
        this -> name = name;
        this -> secondName = secondName;
        this -> gender = gender;
        this -> ward = ward;
    }
    string getName() {
        return this->name;
    }
    string getSurname() {
        return this->surname;
    }
    char getGender() {
        return this->gender;
    }
    string getWard() {
        return this->ward;
    }

    static void inputPatients(map<string, Patient>&patients) {
        ifstream data;
        data.open("pacjenci.txt");
        auto *headers = new string;
        getline(data, *headers);
        delete headers;

        string PESEL, surname, name, secondName, ward;
        char gender;

        while(!data.eof()) {

            data >> PESEL >> surname >> name;
            string temporaryHelp;
            data >> temporaryHelp;
            if(temporaryHelp.size() == 1) {
                secondName = "";
                gender = temporaryHelp.at(0);
            }
            else {
                secondName = temporaryHelp;
                data >> gender;
            }
            data >> ward;

            auto patient = new Patient(surname, name, secondName, gender, ward);
            patients.insert(pair<string, Patient>(PESEL, *patient));

            delete patient;
        }
        data.close();
    }

    static void showPatients(map<string, Patient>&patients) {
        for(auto &pair : patients) {
            cout << pair.first << " " << pair.second.name << " " << pair.second.surname << " " <<
                    pair.second.secondName << pair.second.gender << " " << pair.second.ward << endl;
        }
    }
};
