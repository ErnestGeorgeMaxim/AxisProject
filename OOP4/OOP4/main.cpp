#include <iostream>
#include <vector>
#include <memory>
#include <string>

class MaintenanceRecord {
private:
    std::string description;
    std::string date;
    double cost;

public:
    MaintenanceRecord() : description(""), date(""), cost(0.0) {}
    MaintenanceRecord(const std::string& description, const std::string& date, const double& cost)
        : description(description), date(date), cost(cost) {}

    double getCost() const {
        return this->cost;
    }

    friend std::ostream& operator<<(std::ostream& os, const MaintenanceRecord& mr) {
        os << "Description: " << mr.description << "\n";
        os << "Date       : " << mr.date << "\n";
        os << "Cost       : " << mr.cost << "\n";
        return os;
    }

    ~MaintenanceRecord() = default;
};

class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    double totalMaintenanceCost;
    std::vector<MaintenanceRecord> maintenanceRecords;

public:
    Vehicle() : make(""), model(""), year(0), totalMaintenanceCost(0.0) {}
    Vehicle(const std::string& make, const std::string& model, const int& year)
        : make(make), model(model), year(year), totalMaintenanceCost(0.0) {}

    void addMaintenanceRecord(const MaintenanceRecord& record) {
        maintenanceRecords.push_back(record);
        totalMaintenanceCost += record.getCost();
    }

    double getTotalMaintenanceCost() const {
        return totalMaintenanceCost;
    }

    virtual void displayInfo(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
        v.displayInfo(os);
        os << "Total Maintenance Cost: $" << v.totalMaintenanceCost << "\n";
        for (const auto& record : v.maintenanceRecords) {
            os << record << "\n";
        }
        return os;
    }

    Vehicle& operator+=(const MaintenanceRecord& record) {
        addMaintenanceRecord(record);
        return *this;
    }

    Vehicle& operator-=(const MaintenanceRecord& record) {
        totalMaintenanceCost -= record.getCost();
        return *this;
    }

    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    Car() : numberOfDoors(0), Vehicle() {}
    Car(const std::string& make, const std::string& model, int year, int doors)
        : Vehicle(make, model, year), numberOfDoors(doors) {}

    void displayInfo(std::ostream& os) const override {
        os << "Car             : " << make << " " << model << "\n";
        os << "Year            : " << year << "\n";
        os << "Number of Doors : " << numberOfDoors << "\n";
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;

public:
    Motorcycle() : hasSidecar(false), Vehicle() {}
    Motorcycle(const std::string& make, const std::string& model, int year, bool sideCar)
        : Vehicle(make, model, year), hasSidecar(sideCar) {}

    void displayInfo(std::ostream& os) const override {
        os << "Motorcycle      : " << make << " " << model << "\n";
        os << "Year            : " << year << "\n";
        os << "Has Sidecar     : " << (hasSidecar ? "Yes" : "No") << "\n";
    }
};

class Truck : public Vehicle {
private:
    int capacity;

public:
    Truck() : capacity(0), Vehicle() {}
    Truck(const std::string& make, const std::string& model, int year, int capacity)
        : Vehicle(make, model, year), capacity(capacity) {}

    void displayInfo(std::ostream& os) const override {
        os << "Truck           : " << make << " " << model << "\n";
        os << "Year            : " << year << "\n";
        os << "Capacity        : " << capacity << " tons\n";
    }
};

class VehicleManager {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;

public:
    void addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
        vehicles.push_back(vehicle);
    }

    void displayAllVehicles() const {
        for (const auto& veh : vehicles)
            std::cout << *veh;
    }

    void addMaintenanceToVehicle(size_t index, const MaintenanceRecord& record) {
        if (index < vehicles.size()) {
            *vehicles[index] += record;
        }
    }
};

int main() {
    VehicleManager manager;

    auto car = std::make_shared<Car>("Toyota", "Camry", 2020, 4);
    auto motorcycle = std::make_shared<Motorcycle>("Harley-Davidson", "Sportster", 2018, true);
    auto truck = std::make_shared<Truck>("Ford", "F-150", 2021, 3);

    manager.addVehicle(car);
    manager.addVehicle(motorcycle);
    manager.addVehicle(truck);

    MaintenanceRecord record1("Oil Change", "2024-01-15", 100.0);
    MaintenanceRecord record2("Tire Replacement", "2024-02-20", 400.0);

    manager.addMaintenanceToVehicle(0, record1);
    manager.addMaintenanceToVehicle(0, record2);

    manager.displayAllVehicles();

    return 0;
}
