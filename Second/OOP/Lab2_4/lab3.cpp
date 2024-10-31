#include <iostream>
#include <string>

// Класс COne (без изменений с предыдущей лабораторной)
class COne {
private:
    long l;
    std::string s;

public:
    COne() : l(0), s("") {}
    COne(long l_val, const std::string& s_val) : l(l_val), s(s_val) {}
    COne(const COne& other) : l(other.l), s(other.s) {}
    ~COne() {}

    COne& operator=(const COne& other) {
        if (this != &other) {
            l = other.l;
            s = other.s;
        }
        return *this;
    }

    void print() const {
        std::cout << "COne: l = " << l << ", s = " << s << std::endl;
    }
};

// Класс CTwo с учетом глубокого копирования
class CTwo {
protected:
    double d;
    COne* p;

public:
    CTwo() : d(0.0), p(nullptr) {}
    CTwo(double d_val, COne* p_val) : d(d_val), p(p_val ? new COne(*p_val) : nullptr) {}
    CTwo(const CTwo& other) : d(other.d), p(other.p ? new COne(*other.p) : nullptr) {}
    virtual ~CTwo() { delete p; }

    CTwo& operator=(const CTwo& other) {
        if (this != &other) {
            d = other.d;
            delete p;
            p = other.p ? new COne(*other.p) : nullptr;
        }
        return *this;
    }

    virtual void print() const {
        std::cout << "CTwo: d = " << d;
        if (p) {
            std::cout << ", p -> ";
            p->print();
        } else {
            std::cout << ", p = nullptr" << std::endl;
        }
    }
};

// Новый класс CThree, наследуемый от CTwo
class CThree : public CTwo {
private:
    int additionalField;

public:
    CThree() : CTwo(), additionalField(0) {}
    CThree(double d_val, COne* p_val, int add_field) : CTwo(d_val, p_val), additionalField(add_field) {}
    
    // Конструктор копирования: вызывает конструктор копирования CTwo
    CThree(const CThree& other) : CTwo(other), additionalField(other.additionalField) {}

    // Оператор присваивания с глубоким копированием
    CThree& operator=(const CThree& other) {
        if (this != &other) {
            CTwo::operator=(other);  // Используем оператор присваивания базового класса
            additionalField = other.additionalField;
        }
        return *this;
    }

    // Деструктор
    ~CThree() {}

    // Переопределение метода print
    void print() const override {
        CTwo::print();
        std::cout << "CThree: additionalField = " << additionalField << std::endl;
    }
};

// Тестовая программа
int main() {
    // Создаем объект COne
    COne oneObj(100, "Example String");

    // Создаем объект CTwo, включающий указатель на объект COne
    CTwo twoObj(3.14, &oneObj);

    // Создаем объект CThree, включающий поле additionalField
    CThree threeObj(2.71, &oneObj, 42);

    // Вывод объектов
    oneObj.print();
    twoObj.print();
    threeObj.print();

    return 0;
}

