#include <iostream>

class LinearnaFunkcija
{
    double koef, slob;
public:
    explicit LinearnaFunkcija(double koef, double slob): koef(koef), slob(slob){};
    LinearnaFunkcija(double slob): koef(0), slob(slob){};
    LinearnaFunkcija(): koef(0), slob(0){};
    double DajKoeficijentPravca() const{return koef;};
    double DajSlobodniClan() const{return slob;};
    LinearnaFunkcija& IzmijeniKoeficijentPravca(double d){koef = d; return *this;};
    LinearnaFunkcija& IzmijeniSlobodniClan(double d){slob = d; return *this;};
    friend LinearnaFunkcija operator+(const LinearnaFunkcija& f1, const LinearnaFunkcija& f2);
    LinearnaFunkcija operator+(const double& d);
    friend LinearnaFunkcija operator+(double d, const LinearnaFunkcija& f1);
    friend LinearnaFunkcija operator-(const LinearnaFunkcija& f1, const LinearnaFunkcija& f2);
    LinearnaFunkcija operator-(const double& d);
    friend LinearnaFunkcija operator-(double d, LinearnaFunkcija f1);
    friend LinearnaFunkcija operator-(LinearnaFunkcija f);
    LinearnaFunkcija operator*(double d){
        return LinearnaFunkcija(DajKoeficijentPravca() * d, DajSlobodniClan() * d);
    }
    friend LinearnaFunkcija operator*(double d, LinearnaFunkcija f);
    LinearnaFunkcija operator*(LinearnaFunkcija) = delete;
    LinearnaFunkcija operator/(double d){
        if(!d) throw std::domain_error("Dijeljenje nulom");
        return LinearnaFunkcija(DajKoeficijentPravca() / d, DajSlobodniClan() / d);
    }
    LinearnaFunkcija operator/(LinearnaFunkcija) = delete;
    template <typename Tip>
    LinearnaFunkcija& operator+=(const Tip& f){
        return *this = *this + f;
    }
    template <typename Tip>
    LinearnaFunkcija& operator-=(const Tip& f){
        return *this = *this - f;
    }
    template <typename Tip>
    LinearnaFunkcija& operator*=(const Tip& f){
        return *this = *this * f;
    }
    template <typename Tip>
    LinearnaFunkcija& operator/=(const Tip& f){
        return *this = *this / f;
    }
    LinearnaFunkcija& operator++(){
        return IzmijeniSlobodniClan(DajSlobodniClan() + 1);
    }
    LinearnaFunkcija operator++(int){
        LinearnaFunkcija staro = *this; ++*this; return staro;
    }
    double operator()(double x) const {
        return DajKoeficijentPravca() * x + DajSlobodniClan();
    }
    friend std::ostream& operator<<(std::ostream& tok, LinearnaFunkcija f);
    LinearnaFunkcija DajInverznu();
};

int main() 
{
    LinearnaFunkcija f1, f2(5), f3(4, 2);
    std::cout << f1 << " " << f2 << " "
    << f3 << std::endl; // [k=0,l=0] [k=0,l=4] [k=4,l=2]
    std::cout << f3.DajKoeficijentPravca() << " "
    << f3.DajSlobodniClan() << std::endl; // 4 2
    f1.IzmijeniKoeficijentPravca(3)
    .IzmijeniSlobodniClan(1);
    std::cout << f1 << std::endl; // [k=3,l=1]
    std::cout << f2 + f3 << " " << f3 + 1 << " "
    << 1 + f3 << std::endl; // [k=4,l=7] [k=4,l=3] [k=4,l=3]
    std::cout << f2 - f3 << " " << f3 - 1 << " "
    << 1 - f3 << std::endl; // [k=-4,l=3] [k=4,l=1] [k=-4,l=-1]
    std::cout << f3 * 5 << " " << 5 * f3 << std::endl; // [k=20,l=10] [k=20,l=10]
    std::cout << -f3 << " " << f3 / 5 << std::endl; // [k=-4,l=-2] [k=0.8,l=0.4]
    f2 += f3; std::cout << f2 << std::endl; // [k=4,l=7]
    f2 -= f3; std::cout << f2 << std::endl; // [k=0,l=5]
    f3 += 3; std::cout << f3 << std::endl; // [k=4,l=5]
    f3 -= 3; std::cout << f3 << std::endl; // [k=4,l=2]
    f3 *= 3; std::cout << f3 << std::endl; // [k=12,l=6]
    f3 /= 3; std::cout << f3 << std::endl; // [k=4,l=2]
    std::cout << ++f3 << " ";
    std::cout << f3 << std::endl; // [k=4,l=3] [k=4,l=3]
    std::cout << f3++ << " ";
    std::cout << f3 << std::endl; // [k=4,l=3] [k=4,l=4]
    std::cout << f3(10) << std::endl; // 44
    std::cout << f3.DajInverznu() << std::endl; // [k=0.25,l=1]
    return 0;
}

LinearnaFunkcija operator*(double d, LinearnaFunkcija f)
{
    return f * d;
}

LinearnaFunkcija operator+(const LinearnaFunkcija& f1, const LinearnaFunkcija& f2){
    double k = f1.DajKoeficijentPravca() + f2.DajKoeficijentPravca();
    double n = f1.DajSlobodniClan() + f2.DajSlobodniClan();
    return LinearnaFunkcija(k, n);
}

LinearnaFunkcija LinearnaFunkcija::operator+(const double& d)
{
    return *this + LinearnaFunkcija(d);
}

LinearnaFunkcija operator+(double d, const LinearnaFunkcija& f1)
{
    return f1 + LinearnaFunkcija(d);
}

LinearnaFunkcija operator-(const LinearnaFunkcija& f1, const LinearnaFunkcija& f2){
    double k = f1.DajKoeficijentPravca() - f2.DajKoeficijentPravca();
    double n = f1.DajSlobodniClan() - f2.DajSlobodniClan();
    return LinearnaFunkcija(k, n);
}

LinearnaFunkcija LinearnaFunkcija::operator-(const double& d)
{
    return *this - LinearnaFunkcija(d);
}

LinearnaFunkcija operator-(double d, LinearnaFunkcija f1)
{
    return LinearnaFunkcija(d) - f1;
}

LinearnaFunkcija operator-(LinearnaFunkcija f)
{
    return f.IzmijeniKoeficijentPravca(-f.DajKoeficijentPravca()).IzmijeniSlobodniClan(-f.DajSlobodniClan());
}

std::ostream& operator<<(std::ostream& tok, LinearnaFunkcija f)
{
    return tok<<"[k="<<f.DajKoeficijentPravca()<<",l="<<f.DajSlobodniClan()<<"]";
}

LinearnaFunkcija LinearnaFunkcija::DajInverznu()
{
    if(DajKoeficijentPravca() == 0) throw std::domain_error("Dijeljenje nulom");
    return LinearnaFunkcija(1/DajKoeficijentPravca(),
        -DajSlobodniClan()/DajKoeficijentPravca());
}