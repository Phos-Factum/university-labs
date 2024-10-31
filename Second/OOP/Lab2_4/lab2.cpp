// lab2.cpp

#include <iostream>
#include <string>
#include <cstring>

class COne {
private:
    int n;
    std::string s;

public:
    COne() : n(0), s("") {}

    COne(int n_val, const std::string& s_val) : n(n_val), s(s_val) {}

    COne(const COne& other) : n(other.n), s(other.s) {}

    ~COne() = default;

    COne& operator=(const COne& other) {
        if (this != &other) {
            n = other.n;
            s = other.s;
        }
        return *this;
    }

    void print() const {
        std::cout << "COne: n = " << n << ", s = " << s << std::endl;
    }
};

class CTwo {
private:
    double d;
    COne* p;

public:
    CTwo() : d(0.0), p(nullptr) {}

    CTwo(double d_val, COne* p_val) : d(d_val) {
        p = p_val ? new COne(*p_val) : nullptr;
    }

    CTwo(const CTwo& other) : d(other.d) {
        p = other.p ? new COne(*other.p) : nullptr;
    }

    ~CTwo() {
        delete p;
    }

    CTwo& operator=(const CTwo& other) {
        if (this != &other) {
            d = other.d;
            delete p;
            p = other.p ? new COne(*other.p) : nullptr;
        }
        return *this;
    }

    void print() const {
        std::cout << "CTwo: d = " << d;
        if (p) {
            std::cout << ", p -> ";
            p->print();
        } else {
            std::cout << ", p = nullptr" << std::endl;
        }
    }
};

int main() {
    COne oneObj(42, "Test String");
    CTwo twoObj(3.14, &oneObj);

    std::cout << "Object COne:" << std::endl;
    oneObj.print();

    std::cout << "Object CTwo:" << std::endl;
    twoObj.print();

    return 0;
}

