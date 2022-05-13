#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>


using namespace std;

class AnnualUnemployment {

private:
    vector<float>factors;

public:
    AnnualUnemployment(vector<float> &factors) {

        for(float & factor : factors) {
            this->factors.push_back(factor);
        }
    }

    vector<float>getFactors() {
        return this->factors;
    }

    static void inputAnnualUnemplomentRatios(map<int, AnnualUnemployment> &destinationMap) {

        ifstream data;
        try {
            data.open("stopa_bezrobocia_dots.txt");
            if(!data.good()) {
                throw -1;
            }
        }
        catch (int exception) {
            cout << "Wrong pathname !";
            exit(0);
        }

        auto *firstLine = new string;
        getline(data, *firstLine);

        cout << *firstLine << endl;
        delete firstLine;

        int year;
        float value;
        vector<float>factorsVector;
        for(int j = 1945; j <= 2015; j++) {
            data >> year;
            cout << year << "\t";
            for (int i = 0; i < 12; i++) {
                data >> value;
                factorsVector.push_back(value);
                cout << factorsVector[i] << "\t";
            }
            cout << endl;
            auto *annualUnemployment = new AnnualUnemployment(factorsVector);
            factorsVector.clear();
            destinationMap.insert(pair<int, AnnualUnemployment>(year, *annualUnemployment));
            delete annualUnemployment;
        }
    }

    static void showAnnualUnemployment(map<int, AnnualUnemployment> &destinationVector) {

        for(const auto& year: destinationVector) {
            cout << year.first << "\t";
            for(float value : year.second.factors) {
                cout << value << "\t";
            }
            cout << endl;
        }
    }
};
