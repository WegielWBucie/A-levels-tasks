#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>

#include "Patient.cpp"
#include "XRay.cpp"
#include "Examination.cpp"

int main() {

    map<string, Patient>patients;
    //PESEL / Patient -> (name, surname, gender, ward)
    Patient::inputPatients(patients);

    map<string, list<Examination>>examinations;
    //PESEL / Examination -> testID
    Examination::inputExaminations(examinations);

    map<string, XRay>XRays;
    //testID / XRay -> (testName, cost)
    XRay::inputXRays(XRays);
    
    int mostXRays = 0;
    int xRaysCounter;
    string PESEL;
    for(const auto& patient : examinations) {
        xRaysCounter = 0;
        for(auto examine: patient.second) {
            xRaysCounter++;
        }
        if(xRaysCounter > mostXRays) {
            mostXRays = xRaysCounter;
            PESEL = patient.first;
        }
    }
    cout << "1) \n";
    cout << patients.at(PESEL).getName() << " " << patients.at(PESEL).getSurname() << ", Age: " <<
            PESEL.substr(0,2) << ", XRays: " << mostXRays << endl;

    cout << "2) \n";

    map<string, int>costsPerPerson;
    //PESEL / cost
    for(auto &patient : examinations) {

        costsPerPerson.insert(pair<string, int>(patient.first, 0));
        string thisID;
        for(auto &eachExamination : patient.second) {
            thisID = eachExamination.getTestID();
            costsPerPerson.at(patient.first) += XRays.find(thisID)->second.getCost();
        }
    }

    //wardName / entireAmount
    unordered_map<string, int>costsPerWard;
    map<int, string>sortedCostsPerWard;

    int asd = 0;
    for(auto &costPerPatient : costsPerPerson) {
        if(costsPerWard.find(patients.find(costPerPatient.first)->second.getWard()) == costsPerWard.end()) {
            costsPerWard.insert(pair<string, int>(patients.at(costPerPatient.first).getWard(), costPerPatient.second));
            asd ++;
        }
        else {
            costsPerWard.at(patients.find(costPerPatient.first)->second.getWard()) += costPerPatient.second;
        }
    }
    for(auto &costPerWard : costsPerWard) {
        sortedCostsPerWard.insert(pair<int, string>(costPerWard.second, costPerWard.first));
    }
    for(auto it = sortedCostsPerWard.rbegin(); it != sortedCostsPerWard.rend(); it++) {
        cout << it->second << " -> " << it->first << endl;
    }
//    tootalnie zły sposób na sortowanie, ale nie da sie sortować map, a tego wymagałoby zadanie xD
//    dałoby radę posortować vector, ale i tak tworzylbym nowy kontener
//    sposob zly szczegolnie dlatego, ze jako klucz sluzy suma kosztow, ktora moglaby sie powtorzyc dla
//    paru roznych osrodkow


    sortedCostsPerWard.clear();
    costsPerPerson.clear();
    costsPerWard.clear();

    cout << "3) \n";
    map<string, int>eachXRaysCounters;

    mostXRays = 0;
    for(auto &patient : examinations) {

        for(auto &examination : patient.second) {

            if(eachXRaysCounters.find(examination.getTestID()) == eachXRaysCounters.end()) {
                eachXRaysCounters.insert(pair<string, int>(examination.getTestID(), 1));
            }
            else {
                eachXRaysCounters.at(examination.getTestID())++;
            }
        }
    }
    string xRayID;
    for(auto &counter : eachXRaysCounters) {
        if(counter.second > mostXRays) {
            mostXRays = counter.second;
            xRayID = counter.first;
        }
        counter.second = 0;
    }
    cout << "a) ";
    cout << XRays.at(xRayID).getTestName() << " -> " << mostXRays << endl;

    for(auto &patient : examinations) {
        vector<string>testsIDs;
        for(auto &examination : patient.second) {
            if(find(testsIDs.begin(), testsIDs.end(), examination.getTestID()) == testsIDs.end()) {
                eachXRaysCounters.at(examination.getTestID())++;
                testsIDs.push_back(examination.getTestID());
            }
        }
    }
    mostXRays = 0;
    for(auto &counter : eachXRaysCounters) {
        if(counter.second > mostXRays) {
            mostXRays = counter.second;
            xRayID = counter.first;
        }
        counter.second = 0;
    }
    eachXRaysCounters.clear();
    cout << "b) ";
    cout << XRays.at(xRayID).getTestName() << " -> " << mostXRays << endl;

    int maleCounter = 0;
    int femaleCounter = 0;
    for(auto &patient : patients) {
        if(patient.second.getGender() == 'k') {
            femaleCounter++;
        }
        else {
            maleCounter++;
        }
    }
    cout << "4) \n";
    cout << "Women: " << femaleCounter << "\t" << "Men: " << maleCounter << endl;

    map<int, int>decadesCounter;
    for(auto &patient : patients) {

        int decade = (patient.first.at(0)  - 48) + 1;
        if(decadesCounter.find(decade) == decadesCounter.end()) {
            decadesCounter.insert(pair<int, int>(decade, 1));
        }
        else {
            decadesCounter.at(decade)++;
        }
    }

    cout << "5) \n";
    for(auto &decade : decadesCounter) {
        cout << "Decade: " << decade.first << " --> " << decade.second << endl;
    }
    decadesCounter.clear();
    patients.clear();
    examinations.clear();
    XRays.clear();
}
