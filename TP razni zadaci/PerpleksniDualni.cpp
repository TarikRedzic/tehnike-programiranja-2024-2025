#include <cmath>
#include <iostream>

class Perpleksni
{
    double realni, hiperbolni;
public:
    Perpleksni(double realni = 0, double hiperbolni = 0):
        realni(realni), hiperbolni(hiperbolni){}
    double DajRealni() const {return realni;}
    double DajHiperbolni() const {return hiperbolni;}
    Perpleksni operator+(){return *this;}
    Perpleksni operator-(){
        return {-DajRealni(), -DajHiperbolni()};
    }
    Perpleksni operator++(int){
        Perpleksni t = *this; ++realni; return t;
    }
    Perpleksni& operator++(){
        ++realni; return *this;
    }
    Perpleksni operator+(const Perpleksni& p2){
        return {DajRealni() + p2.DajRealni(), DajHiperbolni() + p2.DajHiperbolni()};
    }
    Perpleksni operator-(const Perpleksni& p2){
        return {DajRealni() - p2.DajRealni(), DajHiperbolni() - p2.DajHiperbolni()};
    }
    Perpleksni operator/(const Perpleksni& p2);
    Perpleksni operator*(const Perpleksni& p2);
    Perpleksni& operator+=(const Perpleksni& p2);
    Perpleksni& operator-=(const Perpleksni& p2);
    Perpleksni& operator*=(const Perpleksni& p2);
    Perpleksni& operator/=(const Perpleksni& p2);
    bool operator==(const Perpleksni& p2);
    bool operator!=(const Perpleksni& p2);
    friend std::ostream& operator<<(std::ostream& tok, const Perpleksni& p);
    friend std::istream& operator>>(std::istream& tok, Perpleksni& p);
    friend double Apsolutna(const Perpleksni& p);
    friend Perpleksni Konjugacija(const Perpleksni& p);
    friend double DajRealni(const Perpleksni& p);
    friend double DajHiperbolni(const Perpleksni& p);
};

class Dualni
{
    double vidljivi, skriveni;
public:
    Dualni(double vidljivi = 0, double skriveni = 0):
        vidljivi(vidljivi), skriveni(skriveni){}
    double DajVidljivi() const {return vidljivi;}
    double DajSkriveni() const {return skriveni;}
    Dualni operator+(){return *this;}
    Dualni operator-(){
        return {-DajVidljivi(), -DajSkriveni()};
    }
    Dualni operator++(int){
        Dualni t = *this; ++vidljivi; return t;
    }
    Dualni& operator++(){
        ++vidljivi; return *this;
    }
    Dualni operator+(const Dualni& p2){
        return {DajVidljivi() + p2.DajVidljivi(), DajSkriveni() + p2.DajSkriveni()};
    }
    Dualni operator-(const Dualni& p2){
        return {DajVidljivi() - p2.DajVidljivi(), DajSkriveni() - p2.DajSkriveni()};
    }
    Dualni operator/(const Dualni& p2);
    Dualni operator*(const Dualni& p2);
    Dualni& operator+=(const Dualni& p2){
        return *this = *this + p2;
    }
    Dualni& operator-=(const Dualni& p2){
        return *this = *this - p2;
    }
    Dualni& operator*=(const Dualni& p2){
        return *this = *this * p2;
    }
    Dualni& operator/=(const Dualni& p2){
        return *this = *this / p2;
    }
    bool operator==(const Dualni& p2){
        return (DajVidljivi() == p2.DajVidljivi() & DajSkriveni() == p2.DajSkriveni());
    }
    bool operator!=(const Dualni& p2){
        return !(*this == p2);
    }
    friend std::ostream& operator<<(std::ostream& tok, const Dualni& p);
    friend std::istream& operator>>(std::istream& tok, Dualni& p);
    friend double Apsolutna(const Dualni& p);
    friend Dualni Konjugacija(const Dualni& p);
    friend double DajVidljivi(const Dualni& p);
    friend double DajSkriveni(const Dualni& p);
};

int main()
{
    Perpleksni p1, p2(2, 2);
    std::cout<<std::boolalpha<< (p1 != p2) <<std::endl;
    std::cout<<p2<<" "<<(-p2)<<" "<<p2<<std::endl;
    std::cout<<p1++<<std::endl;
    std::cout<<++p1<<std::endl;
    std::cout<<std::boolalpha<< (p1 == p2) <<std::endl;
    std::cout<<(p1 + p2)<<std::endl;
    std::cout<<(p1 *= p2)<<std::endl;
    Perpleksni p3{2,3};
    std::cout<<Apsolutna(p3)<<" "<<Apsolutna(Perpleksni(3,2))<<std::endl;
    std::cout<<"Unesite <x,y> formom: ";
    std::cin>>p3;
    std::cout<<p3<<std::endl;
    std::cout<<"Unesite realnom formom: ";
    std::cin>>p3;
    std::cout<<p3<<std::endl;
    return 0;
}

bool Perpleksni::operator==(const Perpleksni& p2)
{
    return (DajRealni() == p2.DajRealni() & DajHiperbolni() == p2.DajHiperbolni());
}

bool Perpleksni::operator!=(const Perpleksni& p2)
{
    return !(*this == p2);
}

Perpleksni Perpleksni::operator*(const Perpleksni& p2)
{
    double r{DajRealni() * p2.DajRealni() + DajHiperbolni() * p2.DajHiperbolni()};
    double h{DajRealni() * p2.DajHiperbolni() + DajHiperbolni() * p2.DajRealni()};
    return {r, h};
}

Perpleksni Perpleksni::operator/(const Perpleksni& p2)
{
    double r = (DajRealni() * p2.DajRealni() - DajHiperbolni() * p2.DajHiperbolni())
        / (p2.DajRealni() * p2.DajRealni() - p2.DajHiperbolni() * p2.DajHiperbolni());
    double h = (p2.DajRealni() * DajHiperbolni() - DajRealni() * p2.DajHiperbolni())
        / (p2.DajRealni() * p2.DajRealni() - p2.DajHiperbolni() * p2.DajHiperbolni());
    return {r, h};
}

Perpleksni& Perpleksni::operator+=(const Perpleksni& p2)
{
    return *this = *this + p2;
}

Perpleksni& Perpleksni::operator-=(const Perpleksni& p2)
{
    return *this = *this - p2;
}

Perpleksni& Perpleksni::operator*=(const Perpleksni& p2)
{
    return *this = *this * p2;
}

Perpleksni& Perpleksni::operator/=(const Perpleksni& p2)
{
    return *this = *this / p2;
}

std::ostream& operator<<(std::ostream& tok, const Perpleksni& p)
{
    return tok<<"<"<<p.DajRealni()<<","<<p.DajHiperbolni()<<">";
}

std::istream& operator>>(std::istream& tok, Perpleksni& p)
{
    tok>>std::ws;
    if(tok.peek() == '<')
    {
        tok.get();
        tok>>p.realni;
        tok>>std::ws; tok.get();
        tok>>p.hiperbolni;
        tok>>std::ws; tok.get();
    }
    else
    {
        tok>>p.realni; 
        p.hiperbolni = 0;
    }
    return tok;
}

double Apsolutna(const Perpleksni& p)
{
    double d = p.DajRealni() * p.DajRealni() - p.DajHiperbolni() * p.DajHiperbolni();
    return (d < 0 ? -sqrt(-d) : sqrt(d));
}

Perpleksni Konjugacija(const Perpleksni& p)
{
    return {p.DajRealni(), -p.DajHiperbolni()};
}

double DajRealni(const Perpleksni& p)
{
    return p.DajRealni();
}

double DajHiperbolni(const Perpleksni& p)
{
    return p.DajHiperbolni();
}

Dualni Dualni::operator/(const Dualni& p2)
{
    double v{DajVidljivi() / p2.DajVidljivi()};
    double s{(p2.DajVidljivi() * DajSkriveni() - DajVidljivi() * p2.DajSkriveni())
        / (p2.DajVidljivi() * p2.DajVidljivi())};
    return {v, s};
}


Dualni Dualni::operator*(const Dualni& p2)
{
    return {DajVidljivi() * p2.DajVidljivi(), 
        DajVidljivi() * p2.DajSkriveni() + DajSkriveni() * p2.DajVidljivi()};
}

std::istream& operator>>(std::istream& tok, Dualni& p)
{
    tok>>std::ws;
    if(tok.peek() == '<')
    {
        tok.get();
        tok>>p.vidljivi;
        tok>>std::ws; tok.get();
        tok>>p.skriveni;
        tok>>std::ws; tok.get();
    }
    else
    {
        tok>>p.vidljivi; 
        p.skriveni = 0;
    }
    return tok;
}

std::ostream& operator<<(std::ostream& tok, const Dualni& p)
{
    return tok<<"<"<<p.DajVidljivi()<<","<<p.DajSkriveni()<<">";
}

double Apsolutna(const Dualni& p)
{
    return fabs(p.DajVidljivi());
}

Dualni Konjugacija(const Dualni& p)
{
    return {p.DajVidljivi(), -p.DajSkriveni()};
}

double DajVidljivi(const Dualni& p)
{
    return p.DajVidljivi();
}

double DajSkriveni(const Dualni& p)
{
    return p.DajSkriveni();
}