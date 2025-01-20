#include <iostream>
#include <fstream>

using namespace std;

class Trans {
protected:
    int v;
    int m;
    int x;
public:
    virtual void info() const = 0;
};

class Car : public Trans {
protected:
    int seats;
    bool glassesIsTone;
    string marka;
public:
    Car(int countSeat) {
        v = 100;
        m = 100;
        x = 0;
        seats = countSeat;
        glassesIsTone = false;
        marka = "";
    }

    void swapTone() {
        glassesIsTone = !glassesIsTone;
    }

    void info() const override {
        cout << "I'm car" << endl;
        cout << "v: " << v << endl; 
    }
};

class Motobyke : public Trans {
protected:
    bool hasKolyaska;
public:
    Motobyke() {
        v = 120;
        m = 120;
        x = 0;
        hasKolyaska = false;
    }

    void info() const override {
        cout << "I'm motobyke" << endl;
        cout << "v: " << v << endl; 
    }

    void addKolyaska () {
        hasKolyaska = true;
    }

};

class Velosiped : public Trans {
protected:
    string color;
public:
    Velosiped() {
        v = 150;
        m = 150;
        x = 0;
    }

    void info() const override {
        cout << "I'm velosiped" << endl;
        cout << "v: " << v << endl; 
    }

    void paint(string color) {
        this->color = color;
    }
};

class Gelentvagen : public Car {
public:
    Gelentvagen() : Car(5) {
        marka = "Gelik";
    }

    void serialize(string filename) {
        ofstream file(filename);

        file << "Weight: " << m << endl;
        file << "Speed:" << v << endl;
        file << "Polojenie: " << x << endl;
        file << "Marka of car: " << marka << endl;
        file << "Count of seats: " << seats << endl;
        
        if (glassesIsTone) {
            file << "Mashine has tone" << endl;
        } else {
            file << "Mashine hasn't tone" << endl;
        }

        file.close();
    }
};

class SpeedMoto : public Motobyke {
private:
    int countV;
//egor kakashka
public:
    SpeedMoto(int count) : Motobyke() {
        countV = count;
    }

    void serialize(string filename) {
        ofstream file(filename);

        file << "Weight: " << m << endl;
        file << "Speed:" << v << endl;
        file << "Polojenie" << x << endl;

        file.close();
    }
};

class SpeedVelosiped : public Velosiped {
private:
    bool dvigatel;
public:
    SpeedVelosiped() : Velosiped() {
        dvigatel = true;
    }
    
};

int main() {
    auto gelik = new Gelentvagen();
    gelik->swapTone();
    gelik->serialize("1.txt");

    return 0;
}