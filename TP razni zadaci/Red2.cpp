#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> struct Cvor
{
    T element;
    Cvor* sljedeci;
};
template <typename Tip> class Red
{
    Cvor<Tip>* celo, *zacelje;
    int velicina;
public:
    Red(): celo(nullptr), zacelje(nullptr), velicina(){};
    ~Red();
    bool DaLiJePrazan()const {return !DajVelicinu();};
    int DajVelicinu()const{return red.size();};
    void UkloniSaCela(){
        if(DajVelicinu() == 0) throw std::domain_error("Prazan red");
        red.resize(DajVelicinu() - 1);
    }
    const Tip& DajCelo() const{return red.at(DajVelicinu() - 1);};
    Tip& DajCelo(){return red.at(DajVelicinu() - 1);};
    const Tip& DajZacelje() const{return red.at(0);};
    Tip& DajZacelje(){return red.at(0);};
    void DodajNaZacelje(Tip element);
};

