#include <iostream>
#include <cmath>
#include "AnnualUnemployment.cpp"
#include <ctime>

using namespace std;

int power(int value, int power) {

    int startValue = value;
    if(power == 0) {
        return 1;
    }
    for(int i=1; i<power; i++) {
        value *= startValue;
    }
    return value;
}

float roundTo(float value, int decimalPlaces) {
    return round(value * power(10, decimalPlaces)) / power(10, decimalPlaces);
}


int main() {

    auto startTime = clock();

    map<int, AnnualUnemployment>annualUnemployment;
    AnnualUnemployment::inputAnnualUnemplomentRatios(annualUnemployment);

    AnnualUnemployment::showAnnualUnemployment(annualUnemployment);

    float maxAverageRatio = 0, minAverageRatio = 100, averageAnnualRatio;
    int yearOfMin, yearOfMax;
    int dangerMonthsCounter = 0;
    for(auto pair : annualUnemployment) {
        averageAnnualRatio = 0;
        for(auto value : pair.second.getFactors()) {
            averageAnnualRatio += value;
            if(value > 10) {
                dangerMonthsCounter++;
            }
        }
        averageAnnualRatio /= 12;
        if(averageAnnualRatio > maxAverageRatio) {
            maxAverageRatio = averageAnnualRatio;
            yearOfMax = pair.first;
        }
        if(averageAnnualRatio < minAverageRatio) {
            minAverageRatio = averageAnnualRatio;
            yearOfMin = pair.first;
        }
    }
    cout << "a) " << dangerMonthsCounter << endl;

    cout << "b) " << endl;
    cout << yearOfMax << "\t" << roundTo(maxAverageRatio, 2) << endl;
    cout << yearOfMin << "\t" <<  roundTo(minAverageRatio, 2) << endl;

    cout << "c) " << endl;
    cout << "Year" << "\tMIN" << "\tMAX" << endl;
    float currentMax, currentMin;
    for(auto pair : annualUnemployment) {

        currentMax = 0;
        currentMin = 1000;
        for(auto value : pair.second.getFactors()) {
            if(value > currentMax) {
                currentMax = value;
            }
            if(value < currentMin) {
                currentMin = value;
            }
        }
        cout << pair.first << "\t" << currentMin << "\t" << currentMax << endl;
    }

    int sequenceLength = 0;
    // 0, not 1, because condition inside loop will be always true for the first transition,
    // (previous value is being set to 100, so every unemployment value will provide incrementation)
    // therefore sequence length will be immediately increased to 1
    int theBiggestLength = 0;
    float previousValue = 100;
    int *firstDate = new int[2]{1945,1};
    int *lastDate = new int[2];
    for(auto pair : annualUnemployment) {

        if(pair.second.getFactors().at(0) <= previousValue) {
            sequenceLength++;
        } else {
            if(sequenceLength > theBiggestLength) {
                theBiggestLength = sequenceLength;
                // month & year

                lastDate[0] = 12;
                lastDate[1] = pair.first - 1;

                firstDate[0] = (12 + (lastDate[0] - sequenceLength) + 1) % 12;
                firstDate[1] = lastDate[1] - (sequenceLength - lastDate[0]) / 12 - 1;

            }
            sequenceLength = 1;
        }

        for(int i=1; i<pair.second.getFactors().size(); i++) {
            if(pair.second.getFactors()[i] <= pair.second.getFactors()[i-1]) {
                sequenceLength++;
            } else {
                if(sequenceLength > theBiggestLength) {
                    theBiggestLength = sequenceLength;
                    lastDate[1] = pair.first;
                    lastDate[0] = i - 1 + 1;
                                // -1 because I check previous month, +1 because months are 1-12

                    firstDate[0] = (12 + (lastDate[0] - sequenceLength) + 1) % 12;
                    firstDate[1] = lastDate[1] - (sequenceLength - lastDate[0]) / 12 - 1;
                }
                sequenceLength = 1;
            }
        }
        previousValue = pair.second.getFactors().at(pair.second.getFactors().size() - 1);
    }
    cout << "d)\n";
    cout << "Month" << "\tYear" << endl;
    cout << firstDate[0] << "\t" << firstDate[1] << endl;
    cout << lastDate[0] << "\t" << lastDate[1] << endl;
    cout << "Length -> " << theBiggestLength << endl;
}
