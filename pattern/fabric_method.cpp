#include <iostream>
#include <string>
#include <memory> // для использования умных указателей
using namespace std;

// Базовый класс игрушки
class Toy {
public:
    virtual void play() const = 0; // Чисто виртуальный метод
    virtual ~Toy() {}             // Виртуальный деструктор
};

// Конкретная игрушка: Машинка
class Car : public Toy {
public:
    void play() const override {
        cout << "Vroom! Машинка едет!" << endl;
    }
};

// Конкретная игрушка: Кукла
class Doll : public Toy {
public:
    void play() const override {
        cout << "Привет! Я кукла!" << endl;
    }
};

// Фабрика игрушек
class ToyFactory {
public:
    // Фабричный метод
    static Toy* createToy(const string& toyType) {
        if (toyType == "car") {
            return new Car(); // Создаём машинку
        } else if (toyType == "doll") {
            return new Doll(); // Создаём куклу
        } else {
            throw invalid_argument("Неизвестный тип игрушки!");
        }
    }
};

int main() {
    // Просим фабрику создать машинку
    auto carToy = ToyFactory::createToy("car");
    carToy->play(); // Вывод: Vroom! Машинка едет!

    // Просим фабрику создать куклу
    auto dollToy = ToyFactory::createToy("doll");
    dollToy->play(); // Вывод: Привет! Я кукла!

    return 0;
}
