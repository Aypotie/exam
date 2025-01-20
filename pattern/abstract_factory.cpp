#include <iostream>
using namespace std;

// Базовый класс для автомобилей
class Car {
public:
    virtual void drive() = 0;
    virtual ~Car() {}
};

// Электромобиль
class ElectricCar : public Car {
public:
    void drive() override {
        cout << "Еду на электричестве" << endl;
    }
};

// Бензиновая машина
class PetrolCar : public Car {
public:
    void drive() override {
        cout << "Еду на бензине" << endl;
    }
};

// Базовый класс для зарядных станций
class ChargingStation {
public:
    virtual void charge() = 0;
    virtual ~ChargingStation() {}
};

// Электрозаправка
class ElectricChargingStation : public ChargingStation {
public:
    void charge() override {
        cout << "Заряжаю электромобиль ⚡🔌" << endl;
    }
};

// Бензозаправка
class PetrolStation : public ChargingStation {
public:
    void charge() override {
        cout << "Заправляю бензин ⛽" << endl;
    }
};

//  Абстрактная фабрика
class CarFactory {
public:
    virtual Car* createCar() = 0;
    virtual ChargingStation* createStation() = 0;
    virtual ~CarFactory() {}
};

class ElectricCarFactory : public CarFactory {
public:
    Car* createCar() override {
        return new ElectricCar();
    }
    ChargingStation* createStation() override {
        return new ElectricChargingStation();
    }
};

class PetrolCarFactory : public CarFactory {
public:
    Car* createCar() override {
        return new PetrolCar();
    }
    ChargingStation* createStation() override {
        return new PetrolStation();
    }
};

int main() {
    CarFactory* factory = new ElectricCarFactory(); 
    Car* myCar = factory->createCar();
    ChargingStation* myStation = factory->createStation();

    myCar->drive();      // "Еду на электричестве "
    myStation->charge(); // "Заряжаю электромобиль"

    delete myCar;
    delete myStation;
    delete factory;
    return 0;
}
