#include <iostream>

using namespace std;

template <typename T>
struct Vector {
private:
    T* data;           // Указатель на массив данных
    int len;           // Текущая длина
    int cap;           // Максимальная емкость
    float loadFactor;  // Коэффициент загрузки

public:
    Vector(int initCap = 16) {
        cap = initCap;
        len = 0;
        data = new T[cap];
        loadFactor = 0.5;
    }

    ~Vector() {
        delete[] data;
    }

    // Текущий размер
    int size() const {
        return len;
    }

    // Увеличение ёмкости массива
    void extend() {
        int newCap = cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i < len; i++) {  
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

    // Добавление элемента в конец
    void pushBack(T value) {
        if (static_cast<float>(len) / cap >= loadFactor) {
            extend();
        }
        data[len] = value;
        len++;
    }

    // Удаление элемента
    void remove(int index) {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }

        for (int i = index; i < len - 1; i++) {
            data[i] = data[i + 1];
        }
        len--;
    }

    // Получение элемента
    T get(int index) const {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }
        return data[index];
    }

    // Получение текущей емкости
    int capacity() const {
        return cap;
    }
};

// Оператор вывода
template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        os << vec.get(i);
        if (i != vec.size() - 1) os << ", ";
    }
    return os;
}

// Пример использования
int main() {
    Vector<int> vec;
    vec.pushBack(1);
    vec.pushBack(2);
    vec.pushBack(3);
    cout << "Vector: " << vec << endl;

    vec.remove(1);
    cout << "After removing index 1: " << vec << endl;

    cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;

    return 0;
}
/*
int main() {
    Vector<int>* vec = new Vector<int>();
    vec->pushBack(10);
    vec->pushBack(20);

    cout << "Vector: " << *vec << endl;

    delete vec; // Вызов деструктора для очистки памяти
    return 0;
}
*/
