#include "longdigit.h"

namespace std{

    void LongDigit::notempty(){
        if(digit.empty())
            digit.push_back(0);
    }

    LongDigit::LongDigit(){
        notempty();
    }

    LongDigit::LongDigit(const string st){
        while(st.size() && !st.back())
            st.pop_back();
        for(char c : st){
            if(!isdigit(c)) break;
            digit.insert(digit.begin(), c - '0');
        }
        notempty();
    }

    LongDigit::LongDigit(unsigned long d){
        while(d){
            digit.push_back(d % 10);
            d /= 10;
        }
        notempty();
    }

    LongDigit::LongDigit(const char* c){
        unsigned i = 0;
        while(c[i] && !(c[i] - '0'))
            ++i;
        while(c[i] && isdigit(c[i])){
            digit.insert(digit.begin(), c[i] - '0');
            ++i;
        }
        notempty();
    }

    LongDigit LongDigit::operator=(LongDigit l){
        digit.clear();
        for(int i : l.digit)
            digit.push_back(i);
        return *this;
    }

    int LongDigit::operator[](int d){
        if(d >= 0 && d < digit.size())
            return digit[digit.size() - d - 1];
        else if(d < 0 && -d <= digit.size())
            return digit[-d - 1];
        return -1;
    }

    unsigned LongDigit::length(){
        return digit.size();
    }

    bool LongDigit::iseven(){
        return (usint) digit[0] % 2 == 0;
    }

    int LongDigit::cmp(const LongDigit l) const
    {
        if(l.digit.size() < digit.size()) return 1;
        if(l.digit.size() > digit.size()) return -1;
        for(int i = l.digit.size() - 1; i >= 0; --i){
            if(l.digit[i] < digit[i]) return 1;
            if(l.digit[i] > digit[i]) return -1;
        }
        return 0;
    }

    bool LongDigit::operator==(const LongDigit l) const
    {
        return this->cmp(l) == 0;
    }

    bool LongDigit::operator!=(const LongDigit l) const
    {
        return this->cmp(l) != 0;
    }

    bool LongDigit::operator>=(const LongDigit l) const
    {
        return this->cmp(l) >= 0;
    }

    bool LongDigit::operator<=(const LongDigit l) const
    {
        return this->cmp(l) <= 0;
    }

    bool LongDigit::operator>(const LongDigit l) const
    {
        return this->cmp(l) > 0;
    }

    bool LongDigit::operator<(const LongDigit l) const
    {
        return this->cmp(l) < 0;
    }

    bool LongDigit::operator!(){
        return digit.size() == 1 && digit[0] == 0;
    }

    LongDigit LongDigit::operator<<(unsigned d){
        LongDigit l = *this;
        if(!l) return l;
        for(unsigned i = 0; i < d; ++i)
            l.digit.insert(l.digit.begin(), 0);
        return l;
    }

    LongDigit LongDigit::operator>>(unsigned d){
        LongDigit l = *this;
        for(unsigned i = 0; i < d; ++i)
            if(!l) return l;
            else l.digit.erase(l.digit.begin());
        return l;
    }

    LongDigit LongDigit::operator+(LongDigit l){
        LongDigit ls = max(*this, l);
        unsigned m, over = 0, i, sum;
        m = min(l.digit.size(), digit.size());
        for(i = 0; i < m; ++i){
            sum = l.digit[i] + digit[i] + over;
            over = sum / 10;
            ls.digit[i] = sum % 10;
        }
        while(over){
            if(i == ls.digit.size()){
                ls.digit.push_back(over);
                over = 0;
            }else{
                ls.digit[i] += over;
                over = ls.digit[i] / 10;
                ls.digit[i++] %= 10;
            }
        }
        return ls;
    }

    LongDigit LongDigit::operator+=(LongDigit l){
        return *this = *this + l;
    }

    LongDigit LongDigit::operator*=(unsigned d){
        return *this = *this * d;
    }

    LongDigit LongDigit::operator++(){
        unsigned i = 0, over = 1, sum;
        do{
            sum = digit[i] + over;
            over = sum / 10;
            digit[i] = sum % 10;
            ++i;
        }while(over && i < digit.size());
        if(over)
            digit.push_back(over);
        return *this;
    }

    LongDigit LongDigit::operator++(int){
        LongDigit l = *this;
        ++(*this);
        return l;
    }

    LongDigit LongDigit::operator*(LongDigit l){
        LongDigit lp;
        unsigned i = 0;
        for(usint d : digit){
            lp += (l * d) << i;
            ++i;
        }
        return lp;
    }

    LongDigit LongDigit::operator*=(LongDigit l){
        *this = *this * l;
        return *this;
    }

    LongDigit LongDigit::operator*(unsigned d){
        LongDigit l;
        if(!d) return l;
        unsigned pr, i = 0;
        unsigned long over = 0;
        for(unsigned len = digit.size(); i < len; ++i){
            pr = (usint) digit[i] * d + over;
            over = pr / 10;
            if(i < len - 1)
                l.digit.push_back(over % 10);
            l.digit[i] = pr % 10;
        }
        while(over){
            l.digit.push_back(over % 10);
            over = over / 10;
            l.digit[i] %= 10;
             ++i;
        }
        return l;
    }

//    pair<LongDigit, LongDigit> LongDigit::division(LongDigit){

//    }

    void LongDigit::swap(LongDigit& l1){
        l1.digit.swap(digit);
    }

    LongDigit operator+(unsigned d, LongDigit l){
        return l + d;
    }

    LongDigit operator*(unsigned d, LongDigit l){
        return l * d;
    }

    istream& operator>>(istream &in, LongDigit &l){
        string d;
        in >> d;
        l.digit.clear();
        for(char c : d){
            if(!isdigit(c)) break;
            l.digit.insert(l.digit.begin(), c - '0');
        }
        return in;
    }

    ostream& operator<<(ostream &out, const LongDigit l){
        for(auto it = l.digit.rbegin(); it != l.digit.rend(); ++it)
            out << (usint) *it;
        return out;
    }

}
