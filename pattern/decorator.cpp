#include <iostream>
using namespace std;

// Базовый интерфейс напитка
class Beverage {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

// Конкретный класс — обычный кофе
class Coffee : public Beverage {
public:
    string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 5.0;
    }
};

// Декоратор, расширяющий функциональность напитка
class BeverageDecorator : public Beverage {
protected:
    Beverage* baseBeverage;
public:
    BeverageDecorator(Beverage* beverage) : baseBeverage(beverage) {}

    virtual string getDescription() const override {
        return baseBeverage->getDescription();
    }

    virtual double cost() const override {
        return baseBeverage->cost();
    }
};

// Добавка: молоко 🥛
class Milk : public BeverageDecorator {
public:
    Milk(Beverage* beverage) : BeverageDecorator(beverage) {}

    string getDescription() const override {
        return baseBeverage->getDescription() + " + Milk";
    }

    double cost() const override {
        return baseBeverage->cost() + 1.5;
    }
};

// Добавка: карамель 🍬
class Caramel : public BeverageDecorator {
public:
    Caramel(Beverage* beverage) : BeverageDecorator(beverage) {}

    string getDescription() const override {
        return baseBeverage->getDescription() + " + Caramel";
    }

    double cost() const override {
        return baseBeverage->cost() + 2.0;
    }
};

int main() {
    Beverage* myCoffee = new Coffee();
    cout << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << endl;

    myCoffee = new Milk(myCoffee);
    cout << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << endl;

    myCoffee = new Caramel(myCoffee);
    cout << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << endl;

    delete myCoffee;
    return 0;
}
