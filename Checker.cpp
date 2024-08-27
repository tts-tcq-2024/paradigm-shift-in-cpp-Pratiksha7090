#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

enum class BreachType { NORMAL, TOO_LOW, TOO_HIGH };

class BatteryParameter {
public:
    string name;
    float minLimit;
    float maxLimit;

    BatteryParameter(string paramName, float min, float max)
        : name(paramName), minLimit(min), maxLimit(max) {}
};

BreachType classifyBreach(float value, const BatteryParameter& parameter) {
    if (value < parameter.minLimit) {
        return BreachType::TOO_LOW;
    }
    if (value > parameter.maxLimit) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}
void printBreachMessage(const BatteryParameter& parameter, BreachType breachType) {
    if (breachType == BreachType::TOO_LOW) {
        cout << parameter.name << " too low!\n";
    } else if (breachType == BreachType::TOO_HIGH) {
        cout << parameter.name << " too high!\n";
    }
}

bool checkAndReportBreach(float value, const BatteryParameter& parameter) {
    BreachType breachType = classifyBreach(value, parameter);
    if (breachType != BreachType::NORMAL) {
        printBreachMessage(parameter, breachType);
        return false;
    }
    return true;
}



bool batteryIsOk(float temperature, float soc, float chargeRate) {
    BatteryParameter temperatureParam("Temperature", 0, 45);
    BatteryParameter socParam("State of Charge", 20, 80);
    BatteryParameter chargeRateParam("Charge Rate", 0, 0.8);

    bool temperatureOk = checkAndReportBreach(temperature, temperatureParam);
    bool socOk = checkAndReportBreach(soc, socParam);
    bool chargeRateOk = checkAndReportBreach(chargeRate, chargeRateParam);

    return temperatureOk && socOk && chargeRateOk;
}

void runTests() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(-5, 70, 0.7) == false);
    assert(batteryIsOk(25, 85, 0.7) == false);
    assert(batteryIsOk(25, 70, 0.9) == false);
    assert(batteryIsOk(50, 85, 0.9) == false);
}

int main() {
    runTests();
    cout << "All tests passed!\n";
}
