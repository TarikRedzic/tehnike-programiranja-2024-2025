#include <iostream>

//stopa ima 12 inca, yard 3 stope
class SAD_Duzina
{
    int inch;
public:
    SAD_Duzina(int yard, int feet, int inch);
    SAD_Duzina(double metri);
    void Ocitaj(int& yard, int& feet, int& inch);
    double DajMetara() const{
        return (inch * 2.54) / 100;
    }
    SAD_Duzina operator+(const SAD_Duzina& l);
    SAD_Duzina& operator+=(const SAD_Duzina& l){
        return *this = *this + l;
    }
    SAD_Duzina& operator+(){
        ++inch; return *this;
    }
    SAD_Duzina operator+(int){
        SAD_Duzina a{*this}; ++inch; return a;
    }
    SAD_Duzina operator*(const SAD_Duzina&) = delete;
    SAD_Duzina operator*(const double& d){
        return SAD_Duzina(0, 0, inch * d);
    }
    friend SAD_Duzina operator*(const double& d, SAD_Duzina l);
    friend double operator/(const SAD_Duzina& a, const SAD_Duzina& b);
    friend std::ostream& operator<<(std::ostream& tok, const SAD_Duzina& l);
};

//galon im 128 unca, barel ima 42 galona
class SAD_ZapreminaTecnosti
{
    int unce;
    static double L ;
public:
    SAD_ZapreminaTecnosti(int barel, int galon, int unce);
    SAD_ZapreminaTecnosti(double litri);
    void Ocitaj(int& barel, int& galon, int& unce);
    double DajLitara() const{
        return unce * L;
    }
    SAD_ZapreminaTecnosti operator+(const SAD_ZapreminaTecnosti& l);
    SAD_ZapreminaTecnosti& operator+=(const SAD_ZapreminaTecnosti& l){
        return *this = *this + l;
    }
    SAD_ZapreminaTecnosti& operator+(){
        ++unce; return *this;
    }
    SAD_ZapreminaTecnosti operator+(int){
        SAD_ZapreminaTecnosti a{*this}; ++unce; return a;
    }
    SAD_ZapreminaTecnosti operator*(const SAD_ZapreminaTecnosti&) = delete;
    SAD_ZapreminaTecnosti operator*(const double& d){
        return SAD_ZapreminaTecnosti(0, 0, unce * d);
    }
    friend SAD_ZapreminaTecnosti operator*(const double& d, SAD_ZapreminaTecnosti l);
    friend double operator/(const SAD_ZapreminaTecnosti& a, const SAD_ZapreminaTecnosti& b);
    friend std::ostream& operator<<(std::ostream& tok, const SAD_ZapreminaTecnosti& l);
};

double SAD_ZapreminaTecnosti::L = 0.02957353;

int main()
{

    return 0;
}


SAD_Duzina::SAD_Duzina(int yard, int feet, int inch)
{
    feet += yard * 3; inch += feet * 12;
    SAD_Duzina::inch = inch;
}

SAD_Duzina::SAD_Duzina(double metri)
{
    double cm = metri * 100;
    SAD_Duzina::inch = cm / 2.54;
}

void SAD_Duzina::Ocitaj(int& yard, int& feet, int& inch)
{
    int f{}, y{}, i{};
    i = this->inch; f = i / 12; i %= 12;
    y = f / 3; f %= 3;
    inch = i; feet = f; yard = y;
}

SAD_Duzina SAD_Duzina::operator+(const SAD_Duzina& l)
{
    return {DajMetara() + l.DajMetara()};
}

SAD_Duzina operator*(const double& d, SAD_Duzina l)
{
    return l * d;
}

double operator/(const SAD_Duzina& a, const SAD_Duzina& b)
{
    return a.inch / b.inch;
}

std::ostream& operator<<(std::ostream& tok, SAD_Duzina l)
{
    int yd, ft, in;
    l.Ocitaj(yd, ft, in);
    tok<<yd<<" yd "<<ft<<" ft "<<in<<" in";
    return tok;
}

SAD_ZapreminaTecnosti::SAD_ZapreminaTecnosti(int barel, int galon, int unce)
{
    galon += barel * 42; unce += galon * 128;
    SAD_ZapreminaTecnosti::unce = unce;
}

SAD_ZapreminaTecnosti::SAD_ZapreminaTecnosti(double litri)
{
    SAD_ZapreminaTecnosti::unce = litri / L;
}

void SAD_ZapreminaTecnosti::Ocitaj(int& barel, int& galon, int& unce)
{
    int b{}, g{}, u{};
    u = this->unce; g = u / 128; u %= 128;
    b = g / 42; g %= 42;
    unce = u; galon = g; barel = b;
}

SAD_ZapreminaTecnosti SAD_ZapreminaTecnosti::operator+(const SAD_ZapreminaTecnosti& l)
{
    return {DajLitara() + l.DajLitara()};
}

SAD_ZapreminaTecnosti operator*(const double& d, SAD_ZapreminaTecnosti l)
{
    return l * d;
}

double operator/(const SAD_ZapreminaTecnosti& a, const SAD_ZapreminaTecnosti& b)
{
    return a.unce / b.unce;
}

std::ostream& operator<<(std::ostream& tok, SAD_ZapreminaTecnosti l)
{
    int yd, ft, in;
    l.Ocitaj(yd, ft, in);
    tok<<yd<<" bbl "<<ft<<" gal "<<in<<" oz";
    return tok;
}