[🏠 Home](../index.md)

``cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int vehCount = 0;

class Vehicle {
protected:
    string make, model;
    int year;
    long int odometer;
    int id;

public:
    Vehicle(string _make, string _model, int _year, long int _odo)
        : make(_make), model(_model), year(_year), odometer(_odo), id(++vehCount) {}

    virtual ~Vehicle() {}

    virtual void checkTireRotation() {
        if (odometer > 50000)
            cout << "Please replace tires.\n";
        else
            cout << "Tire rotation not required yet.\n";
    }

    virtual void checkOil() {
        if (odometer > 5000)
            cout << "Oil needs to be changed.\n";
        else
            cout << "Oil change not required.\n";
    }

    virtual void checkCharge() {
        cout << "Charging not applicable for this vehicle.\n";
    }

    int getId() const { return id; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    long int getOdometer() const { return odometer; }

    void setMake(const string& val) { make = val; }
    void setModel(const string& val) { model = val; }
    void setYear(int val) { year = val; }
    void setOdometer(long int val) { odometer = val; }

    virtual string getType() const = 0;

    virtual void display() const {
        cout << "\n***************************************\n";
        cout << "Vehicle ID: " << id << "\n";
        cout << "Type: " << getType() << "\n";
        cout << "Make: " << make << "\n";
        cout << "Model: " << model << "\n";
        cout << "Year: " << year << "\n";
        cout << "Odometer: " << odometer << "\n";
        cout << "***************************************\n";
    }
};

class GasVehicle : public Vehicle {
public:
    using Vehicle::Vehicle;
    string getType() const override { return "Gas"; }
};

class DieselVehicle : public Vehicle {
public:
    using Vehicle::Vehicle;
    string getType() const override { return "Diesel"; }
};

class ElectricVehicle : public Vehicle {
public:
    using Vehicle::Vehicle;
    void checkOil() override {
        cout << "Electric vehicles do not require oil change.\n";
    }

    void checkCharge() override {
        cout << "Vehicle is charging...\n";
    }

    string getType() const override { return "Electric"; }
};

// Global vehicle list
vector<shared_ptr<Vehicle>> vehicles;

int getInputInt(const string& prompt) {
    int val;
    cout << prompt;
    cin >> val;
    return val;
}

long int getInputLong(const string& prompt) {
    long int val;
    cout << prompt;
    cin >> val;
    return val;
}

string getInputStr(const string& prompt) {
    string val;
    cout << prompt;
    cin >> val;
    return val;
}

void addVehicle() {
    cout << "Enter Vehicle Type:\n0: GAS\n1: DIESEL\n2: ELECTRIC\n";
    int type = getInputInt("Type: ");
    string make = getInputStr("Make: ");
    string model = getInputStr("Model: ");
    int year = getInputInt("Year: ");
    long int odo = getInputLong("Odometer: ");

    shared_ptr<Vehicle> v;
    switch (type) {
        case 0: v = make_shared<GasVehicle>(make, model, year, odo); break;
        case 1: v = make_shared<DieselVehicle>(make, model, year, odo); break;
        case 2: v = make_shared<ElectricVehicle>(make, model, year, odo); break;
        default:
            cout << "Invalid type. Vehicle not added.\n";
            return;
    }

    vehicles.push_back(v);
    cout << "Vehicle added successfully.\n";
}

void listVehicles() {
    if (vehicles.empty()) {
        cout << "No vehicles available.\n";
        return;
    }

    for (const auto& v : vehicles)
        v->display();
}

shared_ptr<Vehicle> findVehicleById(int id) {
    for (const auto& v : vehicles)
        if (v->getId() == id)
            return v;
    return nullptr;
}

void updateVehicle() {
    int id = getInputInt("Enter vehicle ID to update: ");
    auto v = findVehicleById(id);
    if (!v) {
        cout << "Vehicle not found.\n";
        return;
    }

    cout << "1. Update Year\n2. Update Odometer\n";
    int opt = getInputInt("Choice: ");
    if (opt == 1) {
        int year = getInputInt("Enter new year: ");
        v->setYear(year);
    } else if (opt == 2) {
        long int odo = getInputLong("Enter new odometer: ");
        v->setOdometer(odo);
    } else {
        cout << "Invalid option.\n";
    }

    cout << "Vehicle updated successfully.\n";
}

void removeVehicle() {
    int id = getInputInt("Enter vehicle ID to remove: ");
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        if ((*it)->getId() == id) {
            vehicles.erase(it);
            cout << "Vehicle removed.\n";
            return;
        }
    }
    cout << "Vehicle not found.\n";
}

void performMaintenanceCheck(void (Vehicle::*checkFunc)()) {
    int id = getInputInt("Enter vehicle ID: ");
    auto v = findVehicleById(id);
    if (v) {
        (v.get()->*checkFunc)();
    } else {
        cout << "Vehicle not found.\n";
    }
}

int main() {
    int selection;
    do {
        cout << "\n========= Vehicle Management Menu =========\n";
        cout << "1. List Vehicles\n2. Add Vehicle\n3. Update Vehicle\n4. Remove Vehicle\n";
        cout << "5. Check Tire Rotation\n6. Check Oil\n7. Charge Vehicle\n0. Exit\n";
        cout << "Choose: ";
        cin >> selection;

        switch (selection) {
            case 1: listVehicles(); break;
            case 2: addVehicle(); break;
            case 3: updateVehicle(); break;
            case 4: removeVehicle(); break;
            case 5: performMaintenanceCheck(&Vehicle::checkTireRotation); break;
            case 6: performMaintenanceCheck(&Vehicle::checkOil); break;
            case 7: performMaintenanceCheck(&Vehicle::checkCharge); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (selection != 0);

    return 0;
}

```
