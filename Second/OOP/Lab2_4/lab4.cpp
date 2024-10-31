// lab4.cpp

#include <iostream>
#include <string>
#include <vector>

class COne {
private:
    long l;
    std::string s;

public:
    COne() : l(0), s("") {}
    COne(long l_val, const std::string& s_val) : l(l_val), s(s_val) {}
    COne(const COne& other) : l(other.l), s(other.s) {}
    virtual ~COne() {}

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

class CThree : public CTwo {
private:
    int additionalField;

public:
    CThree() : CTwo(), additionalField(0) {}
    CThree(double d_val, COne* p_val, int add_field) : CTwo(d_val, p_val), additionalField(add_field) {}
    CThree(const CThree& other) : CTwo(other), additionalField(other.additionalField) {}

    void print() const override {
        CTwo::print();
        std::cout << "CThree: additionalField = " << additionalField << std::endl;
    }
};

class CFour : public CThree {
private:
    std::string extraField;

public:
    CFour() : CThree(), extraField("") {}
    CFour(double d_val, COne* p_val, int add_field, const std::string& extra) : CThree(d_val, p_val, add_field), extraField(extra) {}
    CFour(const CFour& other) : CThree(other), extraField(other.extraField) {}

    void print() const override {
        CThree::print();
        std::cout << "CFour: extraField = " << extraField << std::endl;
    }
};

// Глобальная функция для вывода всех объектов в массиве
void printAll(CTwo* objects[], int n) {
    for (int i = 0; i < n; ++i) {
        objects[i]->print();
        std::cout << "--------" << std::endl;
    }
}

int main() {
    COne oneObj(100, "Example String");
    CTwo twoObj(3.14, &oneObj);
    CThree threeObj(2.71, &oneObj, 42);
    CFour fourObj(1.61, &oneObj, 42, "Extra Data");

    CTwo* objects[] = {&twoObj, &threeObj, &fourObj};
    int n = sizeof(objects) / sizeof(objects[0]);

    printAll(objects, n);

    return 0;
}
