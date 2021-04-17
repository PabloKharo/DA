#include <iomanip>

#include "long_num.hpp"

const int BASE = 10000;
const int RADIX = 4;

namespace NLongNum {

TLongNum::TLongNum(const std::string &str){
    Data.resize((str.size() + (RADIX - 1)) / RADIX);
    int k = str.size();
    for (size_t i = 0; i < Data.size(); i++) {
        size_t change = std::min(RADIX, k - 0);
        k -= change;
        std::string num = str.substr(k, change);
        Data[i] = atoi(num.c_str());
    }
    DeleteLeadingZeros();
}

TLongNum TLongNum::operator+(const TLongNum &rhs) const
{
    TLongNum res;
    size_t n = std::max(rhs.Data.size(), Data.size());
    res.Data.resize(n+1);
    for (size_t i = 0; i < n; ++i) {
        int sum = res.Data[i];
        if (i < rhs.Data.size()) {
            sum += rhs.Data[i];
        }
        if (i < Data.size()) {
            sum += Data[i];
        }
        res.Data[i] = sum % BASE;
        res.Data[i+1] = sum / BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TLongNum TLongNum::operator+(const long long &rhs) const{
    return (*this) + TLongNum(std::to_string(rhs));
}

TLongNum TLongNum::operator-(const TLongNum &rhs) const
{
    TLongNum res;
    size_t n = Data.size();
    res.Data.resize(n);
    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        int diff = Data[i] - carry;
        if (i < rhs.Data.size()) {
            diff -= rhs.Data[i];
        }

        carry = 0;
        if (diff < 0) {
            carry = 1;
            diff += BASE;
        }
        res.Data[i] = diff % BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TLongNum TLongNum::operator-(const long long &rhs) const{
    return (*this) - TLongNum(std::to_string(rhs));
}

TLongNum TLongNum::operator*(const TLongNum &rhs) const
{
    size_t n = Data.size() * rhs.Data.size();
    TLongNum res;
    res.Data.resize(n + 1);
    for(size_t i = 0; i < Data.size(); ++i)
    {
        for(size_t j = 0; j < rhs.Data.size(); ++j)
        {
            int multi = rhs.Data[j] * Data[i] + res.Data[i+j];
            res.Data[i+j] = multi % BASE;
            res.Data[i+j+1] += multi / BASE;
        }
    }
    res.DeleteLeadingZeros();
    return res;
}

TLongNum TLongNum::operator*(const long long &rhs) const{
    return (*this) * TLongNum(std::to_string(rhs));
}

TLongNum TLongNum::operator^(const TLongNum &rhs) const{
    if (rhs.IsZero()){
		return TLongNum("1");
    }
	else if (rhs.Data.front() % 2 == 1){
		return (*this ^ (rhs - 1)) * (*this);
    }
	else {
		TLongNum powed = (*this) ^ (rhs/2);
		return powed * powed;
    }
}

TLongNum TLongNum::operator^(const long long &rhs) const{
    return (*this) ^ TLongNum(std::to_string(rhs));
}

TLongNum TLongNum::operator/(const TLongNum &rhs) const{
    TLongNum res, rem;  
    int i = Data.size() - 1;
    while(i >= 0){
        while(rem < rhs){
            if (i >= 0) {
                rem = (rem * BASE) + Data[i];
                res = res * BASE;
                i--;
            }else {
                break;
            }
        }
        if (i < 0 && rem < rhs) {
            break;
        }

        int x = 0;
        int l = 0;
        int r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            TLongNum eq = rhs * m;
            if (eq == rem) {
                x = m;
                break;
            }else if (eq < rem) {
                x = m;
                l = m + 1;
            }else if (eq > rem) {
                r = m - 1;
            }
        }
        res = res + x;
        rem = rem - rhs * x;
    }
    res.DeleteLeadingZeros();
    return res;
}

TLongNum TLongNum::operator/(const long long &rhs) const{
    return (*this) / TLongNum(std::to_string(rhs));
}

bool TLongNum::operator>(const TLongNum &rhs) const
{
    if (Data.size() != rhs.Data.size()) {
        return Data.size() > rhs.Data.size();
    }

    for (int i = Data.size() - 1; i >= 0; --i) {
        if (Data[i] != rhs.Data[i]) {
            return Data[i] > rhs.Data[i];
        }
    }
    return false;
}

bool TLongNum::operator<(const TLongNum &rhs) const
{
    if (Data.size() != rhs.Data.size()) {
        return Data.size() < rhs.Data.size();
    }

    for (int i = Data.size() - 1; i >= 0; --i) {
        if (Data[i] != rhs.Data[i]) {
            return Data[i] < rhs.Data[i];
        }
    }
    return false;
}

bool TLongNum::operator==(const TLongNum &rhs) const
{
    if (Data.size() != rhs.Data.size()) {
        return false;
    }

    for (int i = Data.size() - 1; i >= 0; --i) {
        if (Data[i] != rhs.Data[i]) {
            return false;
        }
    }
    return true;
}


void TLongNum::DeleteLeadingZeros()
{
    while (!Data.empty() && Data.back() == 0){
        Data.pop_back();
    }
}

bool TLongNum::IsZero() const{
    return Data.empty();
}

std::istream& operator>>(std::istream &in, TLongNum &rhs)
{
    std::string str;
    in >> str;
    rhs = TLongNum(str);
    return in;
}

std::ostream& operator<<(std::ostream &out, const TLongNum &rhs)
{
    if (rhs.Data.empty()) {
        out << "0";
        return out;
    }

    out << rhs.Data.back();
    for (int i = rhs.Data.size() - 2; i >= 0; --i) {
        out << std::setfill('0') << std::setw(RADIX) << rhs.Data[i];
    }
    return out;
}


}
