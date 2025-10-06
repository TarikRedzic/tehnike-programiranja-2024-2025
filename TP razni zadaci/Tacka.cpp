#include <iostream>

class Tacka
{
    double x, y;
public:
    Tacka(): x(0), y(0){}
    Tacka(double x, double y): x(x), y(y){}
    void PostaviPoziciju(double x, double y){
        this->x = x; this->y = y;
    }
    void PostaviPoziciju(std::pair<double, double> par){
        this->x = par.first; this->y = par.second;
    }
    double DajX() const{return x;}
    double DajY() const{return y;}
    bool DaLiJeUKoordinatnomPocetku() const{
        return (x == 0 && y == 0);
    }
    void Transliraj(double dx, double dy){
        x += dx; y += dy;
    }
    void Rotiraj(double ugao);
    void Rotiraj(std::pair<double, double> par, double ugao);
};
//netacno
class KrugURavni : public Tacka
{
    double r;
public:
    KrugURavni(): r(0), Tacka(){}
    KrugURavni(const Tacka& t, double r): 
        Tacka(t.DajX(), t.DajY()), r(r){}
    KrugURavni(double x, double y, double r): Tacka(x, y), r(r){}
    void PostaviPoluprecnik(double r){
        if(r < 0) throw std::domain_error("Neispravan poluprecnik");
        this->r = r;
    }
    double DajPoluprecnik() const;
};

int main()
{

    return 0;
}

void Tacka::Rotiraj(double ugao)
{

}