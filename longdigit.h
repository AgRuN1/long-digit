#ifndef LONGDIGIT_H
#define LONGDIGIT_H

#include <string>
#include <cctype>
#include <iostream>

namespace std{

    typedef unsigned short usint;

    class LongDigit{

        string digit;

        void notempty();
    public:
        LongDigit();
        LongDigit(const string);
        LongDigit(unsigned long);
        LongDigit(const char*);

        LongDigit operator=(LongDigit);

        int operator[](int);
        unsigned length();
        bool iseven();

        int cmp(const LongDigit) const;
        bool operator==(const LongDigit) const;
        bool operator!=(const LongDigit) const;
        bool operator>=(const LongDigit) const;
        bool operator<=(const LongDigit) const;
        bool operator>(const LongDigit) const;
        bool operator<(const LongDigit) const;
        bool operator!();

        LongDigit operator<<(unsigned);
        LongDigit operator>>(unsigned);

        LongDigit operator+(LongDigit);
        LongDigit operator+=(LongDigit);
        LongDigit operator*=(unsigned);
        LongDigit operator++();
        LongDigit operator++(int);

        LongDigit operator*(LongDigit);
        LongDigit operator*=(LongDigit);
        LongDigit operator*(unsigned);

//        LongDigit pow(LongDigit);
//        pair<LongDigit, LongDigit> division(LongDigit);

        void swap(LongDigit&);

        friend LongDigit operator+(unsigned, LongDigit);
        friend LongDigit operator*(unsigned, LongDigit);

        friend istream& operator>>(istream&, LongDigit&);
        friend ostream& operator<<(ostream&, const LongDigit);
    };

    void swap(LongDigit&, LongDigit&);

    istream& operator>>(istream&, LongDigit&);
    ostream& operator<<(ostream&, const LongDigit);

}
#endif // LONGDIGIT_H
