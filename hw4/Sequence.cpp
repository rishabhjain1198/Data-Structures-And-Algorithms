// Sequence.cpp

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Complex
{
public:
    Complex(double r = 0, double i = 0)
    :  m_real(r), m_imag(i)
    {}
    double real() const { return m_real; }
    double imag() const { return m_imag; }
private:
    double m_real;
    double m_imag;
};

int main()
{
    
    Sequence<int> si;
    Sequence<string> ss;
    assert(ss.empty());
    assert(ss.size() == 0);
    assert(ss.insert("Hello") == 0);
    assert(si.insert(10) == 0);
    assert(si.erase(0));
    assert(ss.remove("Goodbye") == 0);
    assert(ss.find("Hello") == 0);
    string s;
    assert(ss.get(0, s));
    assert(ss.set(0, "Hello"));
    Sequence<string> ss2(ss);
    ss2.swap(ss);
    ss2 = ss;
    assert(subsequence(ss,ss2) == 0);
    assert(subsequence(si,si) == -1);
    interleave(ss,ss2,ss);
    interleave(si,si,si);
    return 1;
}
