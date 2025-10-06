#include <iostream>
#include <cmath>

class Kompleksni 
{
    double re, im;
public:
    Kompleksni(double re = 0, double im = 0) : re(re), im(im) {}
    friend Kompleksni operator +(const Kompleksni &a) { return a; }
    friend Kompleksni operator -(const Kompleksni &a) { return {-a.re, -a.im}; }
    friend Kompleksni operator +(const Kompleksni &a, const Kompleksni &b) {
    return {a.re + b.re, a.im + b.im};
    }
    friend Kompleksni operator -(const Kompleksni &a, const Kompleksni &b) {
    return {a.re - b.re, a.im - b.im};
    }
    friend Kompleksni operator *(const Kompleksni &a, const Kompleksni &b) {
    return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
    }
    friend Kompleksni operator /(const Kompleksni &a, const Kompleksni &b) {
    double pomocna = b.re * b.re + b.im * b.im;
    return {(a.re * b.re + a.im * b.im) / pomocna,
    (a.im * b.re - a.re * b.im) / pomocna};
    }
    friend bool operator ==(const Kompleksni &a, const Kompleksni &b) {
    return a.re == b.re && a.im == b.im;
    }
    friend bool operator !=(const Kompleksni &a, const Kompleksni &b) {
    return !(a == b);
    }
    friend Kompleksni &operator +=(Kompleksni &a, const Kompleksni &b) {
    a.re += b.re; a.im += b.im;
    return a;
    }
    friend Kompleksni &operator -=(Kompleksni &a, const Kompleksni &b) {
    a.re -= b.re; a.im -= b.im;
    return a;
    }
    friend Kompleksni &operator *=(Kompleksni &a, const Kompleksni &b) {
    double pomocna = a.re * b.im + a.im * b.re;
    a.re = a.re * b.re - a.im * b.im; a.im = pomocna;
    return a;
    }
    friend Kompleksni &operator /=(Kompleksni &a, const Kompleksni &b) {
    double pom1 = a.im * b.re - a.re * b.im, pom2 = b.re * b.re + b.im * b.im;
    a.re = (a.re * b.re + a.im * b.im) / pom2; a.im = pom1 / pom2;
    return a;
    }
    friend std::ostream &operator <<(std::ostream &tok, const Kompleksni &a);
    friend std::istream &operator >>(std::istream &tok, Kompleksni &a);
    friend double real(const Kompleksni &a) { return a.re; }
    friend double imag(const Kompleksni &a) { return a.im; }
    friend double abs(const Kompleksni &a) {
    return std::sqrt(a.re * a.re + a.im * a.im);
    }
    friend double arg(const Kompleksni &a) { return std::atan2(a.im, a.re); }
    friend Kompleksni conj(const Kompleksni &a) { return {a.re, -a.im}; }
    friend Kompleksni sqrt(const Kompleksni &a) {
    double rho = std::sqrt(abs(a)), phi = arg(a) / 2;
    return {rho * std::cos(phi), rho * std::sin(phi)};
    }
};
std::istream &operator >>(std::istream &tok, Kompleksni &a) 
{
    double temp{};
    bool rez = false;
    tok>>std::ws;
    if(tok.peek() == 'i') {a.re = temp; a.im = 1;}
    tok>>temp;
    char znak;
    while(tok.peek() == ' ') znak = tok.get();
    if(tok.peek() == '+' || tok.peek() == '-')
    {
        a.re = temp;
        if(tok.peek() == 'i') {a.re = temp; a.im = 1;};
        tok>>temp;
        a.im = temp;
    }
    else if(tok.peek() == '\n')
    {
        a.re = temp; a.im = 0;
    }
    else if(tok.peek() == 'i') {a.re = 0; a.im = temp;};
    return tok;
}

std::ostream &operator <<(std::ostream &tok, const Kompleksni &a) 
{
    if(a.re != 0) tok<<a.re;
    if(a.im > 0 && a.re != 0) tok<<"+";
    if(a.im < 0)
    {
        if(a.im == -1) tok<<"-i";
        else tok<<a.im<<"i";
    } 
    else if(a.im == 1) tok<<"i";
    else if(a.im != 0) tok<<a.im<<"i";
    else if(a.im == 0 && a.re == 0) tok<<0;
    return tok;
}

int main()
{
    Kompleksni k1(2,3), k2, k3(2, -1), k4(3, 1), k5(0, -5), k6(3,0);
    std::cout<<k1<<" "<<k2<<" "<<k3<<" "<<k4<<" "<<k5<<" "<<k6<<"\n";
    Kompleksni k7;
    std::cout<<"Unesi novi broj: ";
    std::cin>>k7;
    std::cout<<k7<<std::endl;
}