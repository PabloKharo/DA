#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

namespace NLongNum
{

class TLongNum
{
    public:
        TLongNum() = default;
        TLongNum(const std::string &str);

        friend std::istream& operator>>(std::istream &in, TLongNum &rhs);
        friend std::ostream& operator<<(std::ostream &out, const TLongNum &rhs);

        TLongNum operator+(const TLongNum &rhs) const;
        TLongNum operator+(const long long &rhs) const;

        TLongNum operator-(const TLongNum &rhs) const;
        TLongNum operator-(const long long &rhs) const;

        TLongNum operator*(const TLongNum &rhs) const;
        TLongNum operator*(const long long &rhs) const;

        TLongNum operator^(const TLongNum &rhs) const;
        TLongNum operator^(const long long &rhs) const;

        TLongNum operator/(const TLongNum &rhs) const;
        TLongNum operator/(const long long &rhs) const;

        bool operator<(const TLongNum &rhs) const;
        bool operator>(const TLongNum &rhs) const;
        bool operator==(const TLongNum &rhs) const;
        bool IsZero() const;

    private:
        void DeleteLeadingZeros();
        std::vector<int> Data;
};

}
