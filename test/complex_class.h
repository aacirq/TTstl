#ifndef TTSTL_TEST_COMPLEX_CLASS_H
#define TTSTL_TEST_COMPLEX_CLASS_H

#include <iostream>
#include <string>
#include <cstring>

struct ComplexClass {
    int n_i;
    double n_d;
    std::string str;
    char *c;
    ComplexClass() : n_i(1), n_d(1.0), str(), c(nullptr) { }

    ComplexClass(int i, double d, const std::string &s, const char *ptr)
    : n_i(i), n_d(d), str(s), c(nullptr) {
        set_char_array(ptr);
    }

    ComplexClass(const ComplexClass &rhs)
    : ComplexClass(rhs.n_i, rhs.n_d, rhs.str, rhs.c) { }

    ~ComplexClass() {
        if (c != nullptr)
            delete [] c;
    }

    void swap(ComplexClass &rhs) {
        using std::swap;
        swap(n_i, rhs.n_i);
        swap(n_d, rhs.n_d);
        swap(str, rhs.str);
        swap(c, rhs.c);
    }

    ComplexClass &operator = (ComplexClass rhs) {
        swap(rhs);
        return *this;
    }

    bool operator == (const ComplexClass &rhs) const {
        bool part_flag = (n_i == rhs.n_i) && (n_d == rhs.n_d) && (str == rhs.str);
        if (part_flag && (c == nullptr && rhs.c == nullptr))
            return true;
        if (part_flag && (c != nullptr && rhs.c != nullptr))
            return !strcmp(c, rhs.c);
        return false;
    }

    bool operator != (const ComplexClass &rhs) const {
        return !(operator==(rhs));
    }
private:
    void set_char_array(const char *src) {
        if (c != nullptr) {
            delete [] c;
            c = nullptr;
        }
        if (src == nullptr) return;
        size_t sz = strlen(src);
        c = new char[sz];
        strcpy(c, src);
    }
};

#endif /* TTSTL_TEST_COMPLEX_CLASS_H */